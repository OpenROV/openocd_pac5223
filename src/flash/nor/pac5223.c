#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "imp.h"
#include "helper/binarybuffer.h"
#include <target/cortex_m.h>

#include "pac5223.h"




static const struct command_registration pac5223_command_handlers[] = 
{
	{
		.name = "chip-erase",
		.handler = pac5223_handle_chip_erase_command,
		.mode = COMMAND_EXEC,
		.help = "Erase the entire Flash by using the Chip"
			"Erase feature in the Device Service Unit (DSU).",
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
	.commands 			= pac5223_command_handlers,
	.flash_bank_command	= pac5223_flash_bank_command,
	.erase 				= pac5223_erase,
	.protect 			= pac5223_protect,
	.write 				= pac5223_write,
	.read 				= default_flash_read,
	.probe 				= pac5223_probe,
	.auto_probe 		= pac5223_probe,
	.erase_check 		= default_flash_blank_check,
	.protect_check 		= pac5223_protect_check,
};
