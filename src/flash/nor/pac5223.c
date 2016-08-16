#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "imp.h"
#include "helper/binarybuffer.h"
#include <target/cortex_m.h>

#include "pac5223.h"

// Base registers
#define PAC5XXX_FLASH_BASE                     		(0x00000000UL)

#define PAC5XXX_PERIPH_BASE 						(0x40000000UL)
#define PAC5XXX_MEMCTL_BASE 						(PAC5XXX_PERIPH_BASE + 0x20000)

// Memory Controller Register Addresses
#define PAC5XXX_MEMCTL_FLASHLOCK					(PAC5XXX_MEMCTL_BASE + 0x0)		// [31:0] - Must be written to correct key to allow write to page

#define PAC5XXX_MEMCTL_FLASHSTATUS					(PAC5XXX_MEMCTL_BASE + 0x4)
#define PAC5XXX_MEMCTL_FLASHSTATUS_PERASE			(1 << 1) 						// [1] - 1b: Erase in progress. 0b: erase finished or not in progress
#define PAC5XXX_MEMCTL_FLASHSTATUS_WRITE 			(1 << 0)						// [0] - 1b: Buffered write in progress. 0b: BW finished or not in progress

#define PAC5XXX_MEMCTL_FLASHPAGE					(PAC5XXX_MEMCTL_BASE + 0x8)		// [4:0] - Select page to write/erase

#define PAC5XXX_MEMCTL_FLASHPERASE					(PAC5XXX_MEMCTL_BASE + 0x14)	// [31:0] - Must be written to correct key to allow page erase

// Memory controller definitions
#define PAC5XXX_FLASH_LOCK_FLASHWRITE_KEY   		(0xAAAAAAAA)          			// Allow write to any FLASH pages not protected by RW bits
#define PAC5XXX_FLASH_LOCK_PERASE_KEY       		(0xA5A55A5A)          			// Allow write to FLASHPERASE register to erase FLASH pages

#define FLASH_ERASE_TIMEOUT 100
#define FLASH_WRITE_TIMEOUT 5

// Data structures
struct pac5223_flash_bank 
{
	int probed;
};

// Methods

static inline int pac5223_get_flash_status(struct flash_bank *bank, uint32_t *status)
{
	struct target *target = bank->target;
	return target_read_u32( target, PAC5XXX_MEMCTL_FLASHSTATUS, status );
}

static int pac5223_wait_status_busy( struct flash_bank *bank, int timeout )
{
	struct target *target = bank->target;
	uint32_t status;
	int retval = ERROR_OK;

	// Wait for the write or erase operation to complete or timeout
	for(;;) 
	{
		retval = pac5223_get_flash_status( bank, &status );

		if (retval != ERROR_OK)
			return retval;

		LOG_DEBUG("status: 0x%" PRIx32 "", status);

		// If PERASE and WRITE registers are both 0, operation is complete
		if( ( ( status & PAC5XXX_MEMCTL_FLASHSTATUS_PERASE ) && ( status & PAC5XXX_MEMCTL_FLASHSTATUS_WRITE ) ) == 0 )
			break;

		if (timeout-- <= 0) 
		{
			LOG_ERROR("timed out waiting for flash");
			return ERROR_FAIL;
		}

		alive_sleep(1);
	}

	return retval;
}

static int pac5223_erase(struct flash_bank *bank, int first, int last)
{
	struct target *target = bank->target;
	int i;

	// Make sure target is halted
	if (bank->target->state != TARGET_HALTED) 
	{
		LOG_ERROR("Target not halted");
		return ERROR_TARGET_NOT_HALTED;
	}

	// Erase each page
	for( i = first; i <= last; ++i ) 
	{
		// Unlock flash write
		retval = target_write_u32( target, PAC5XXX_MEMCTL_FLASHLOCK_LOCK, PAC5XXX_FLASH_LOCK_FLASHWRITE_KEY );
		if (retval != ERROR_OK)
			return retval;

		// Write the page to erase
		retval = target_write_u32( target, PAC5XXX_MEMCTL_FLASHPAGE, i );
		if (retval != ERROR_OK)
			return retval;

		// Unlock the erase page
		retval = target_write_u32( target, PAC5XXX_MEMCTL_FLASHPERASE, PAC5XXX_FLASH_LOCK_PERASE_KEY );
		if (retval != ERROR_OK)
			return retval;
		
		// Wait for erase to complete or time out
		retval = pac5223_wait_status_busy( bank, FLASH_ERASE_TIMEOUT );
		if (retval != ERROR_OK)
			return retval;

		bank->sectors[i].is_erased = 1;
	}

	return ERROR_OK;
}

static int pac5223_protect(struct flash_bank *bank, int set, int first, int last)
{
	struct pac5223_flash_bank *pac5223_info = NULL;
	struct target *target = bank->target;

	LOG_DEBUG("PROTECT NOT YET IMPLEMENTED");

	return ERROR_OK;
}

static int pac5223_write(struct flash_bank *bank, const uint8_t *buffer, uint32_t offset, uint32_t count)
{
	struct target *target = bank->target;
	uint8_t *new_buffer = NULL;

	// Make sure target is halted
	if( bank->target->state != TARGET_HALTED ) 
	{
		LOG_ERROR("Target not halted");
		return ERROR_TARGET_NOT_HALTED;
	}

	// Check offset alignment - PAC5223 requires half-word (16bit) alignment
	if( offset & 0x1 ) 
	{
		LOG_ERROR("offset 0x%" PRIx32 " breaks required 2-byte alignment", offset);
		return ERROR_FLASH_DST_BREAKS_ALIGNMENT;
	}

	// Check to see if bytecount breaks half-word alignment.
	// If so, create a copy of the buffer with an additional padding byte to satisfy alignment
	if (count & 1) 
	{
		new_buffer = malloc(count + 1);

		if (new_buffer == NULL) 
		{
			LOG_ERROR("odd number of bytes to write and no memory for padding buffer");
			return ERROR_FAIL;
		}

		LOG_INFO("odd number of bytes to write, padding with 0xff");

		buffer = memcpy(new_buffer, buffer, count);
		new_buffer[count++] = 0xff;
	}

	uint32_t words_remaining = count / 2;

	int retval;

	// Write each word
	while( words_remaining > 0 ) 
	{
		uint16_t value;

		// Fetch the current value to write
		memcpy( &value, buffer, sizeof(uint16_t) );

		// Write the flashlock key to allow writes
		retval = target_write_u32( target, PAC5XXX_MEMCTL_FLASHLOCK_LOCK, PAC5XXX_FLASH_LOCK_FLASHWRITE_KEY );
		if (retval != ERROR_OK)
			break;

		// Write the half word to flash
		retval = target_write_u16(target, bank->base + offset, value);
		if (retval != ERROR_OK)
			break;

		// Wait for the write to complete
		retval = pac5223_wait_status_busy( bank, FLASH_WRITE_TIMEOUT );
		if (retval != ERROR_OK)
			break;

		words_remaining--;
		buffer += 2;
		offset += 2;
	}

	if (new_buffer)
	{
		free(new_buffer);
	}

	return retval;
}

static int pac5223_probe( struct flash_bank *bank )
{
	struct pac5223_flash_bank *pac5223_info = bank->driver_priv;

	int i;

	uint16_t flash_size_in_kb;
	uint16_t max_flash_size_in_kb;
	uint32_t device_id;

	// Set base flash address
	uint32_t base_address 		= PAC5XXX_FLASH_BASE;

	// Set bank info
	pac5223_info->probed 		= 0;

	// 32 1Kb pages
	int num_pages = 32;
	int page_size = 1024;

	// if sector structs exist, free them before proceeding
	if( bank->sectors ) 
	{
		free( bank->sectors );
		bank->sectors = NULL;
	}

	// Set bank info and allocate sector structures
	bank->base 			= base_address;
	bank->size 			= ( num_pages * page_size );
	bank->num_sectors 	= num_pages;
	bank->sectors 		= malloc( sizeof(struct flash_sector) * num_pages );

	// Set sector info
	for( i = 0; i < num_pages; i++ ) 
	{
		bank->sectors[i].offset 		= i * page_size;
		bank->sectors[i].size 			= page_size;
		bank->sectors[i].is_erased 		= -1;
		bank->sectors[i].is_protected 	= 1;
	}

	// Mark bank as probed
	pac5223_info->probed = 1;

	return ERROR_OK;
}

static int pac5223_auto_probe(struct flash_bank *bank)
{
	struct pac5223_flash_bank *pac5223_info = bank->driver_priv;

	if (pac5223_info->probed)
	{
		// Already probed
		return ERROR_OK;
	}
	else
	{
		// Execute probe
		return pac5223_probe( bank );
	}
}

static int pac5223_protect_check(struct flash_bank *bank)
{
	struct pac5223_flash_bank *pac5223_info = bank->driver_priv;

	// TODO: Read write protection status of all sectors
	LOG_DEBUG("PROTECT_CHECK NOT YET IMPLEMENTED");

	return ERROR_OK;
}

FLASH_BANK_COMMAND_HANDLER(pac5223_flash_bank_command)
{
	struct pac5223_flash_bank *pac5223_info;

	if (CMD_ARGC < 6)
		return ERROR_COMMAND_SYNTAX_ERROR;

	pac5223_info = malloc(sizeof(struct pac5223_flash_bank));

	bank->driver_priv = pac5223_info;
	pac5223_info->probed = 0;

	return ERROR_OK;
}

COMMAND_HANDLER(pac5223_handle_info_command)
{
	LOG_DEBUG("INFO NOT YET IMPLEMENTED");
	return ERROR_OK;
}

static const struct command_registration pac5223_exec_command_handlers[] = 
{
	{
		.name = "info",
		.handler = pac5223_handle_info_command,
		.mode = COMMAND_EXEC,
		.usage = "N/A",
		.help = "Get chip info"
	}
	COMMAND_REGISTRATION_DONE
};

static const struct command_registration pac5223_command_handlers[] = 
{
	{
		.name = "pac5223",
		.mode = COMMAND_ANY,
		.help = "PAC5223 flash command group",
		.usage = "",
		.chain = pac5223_exec_command_handlers,
	},
	COMMAND_REGISTRATION_DONE
};

struct flash_driver pac5223_flash = 
{
	.name 				= "pac5223",
	.commands 			= pac5223_command_handlers,		//. Additional chip specific commands
	.flash_bank_command	= pac5223_flash_bank_command,	//. Flash bank setup
	.erase 				= pac5223_erase,				//. Erase sectors
	.protect 			= pac5223_protect,				//. Enable or disable protection for sectors
	.write 				= pac5223_write,				// Write X bytes to offset position
	.read 				= default_flash_read,			//. Read X bytes from offset position
	.probe 				= pac5223_probe,				//. Get target information by reading directly from the target
	.auto_probe 		= pac5223_auto_probe,			//.
	.erase_check 		= default_flash_blank_check,	//. Check to see if flash is empty
	.protect_check 		= pac5223_protect_check,		//. Check to see if all sectors are unlocked
};
