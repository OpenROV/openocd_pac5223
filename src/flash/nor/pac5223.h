#ifndef OPENOCD_FLASH_NOR_PAC5223_H
#define OPENOCD_FLASH_NOR_PAC5223_H


#define PAC5XXX_PERIPH_BASE 					(0x40000000UL)
#define PAC5XXX_MEMCTL_BASE 					(PAC5XXX_PERIPH_BASE + 0x20000)

#define PAC5XXX_FLASH_BASE                      (0x00000000UL)                              /*!< FLASH        Base Address            */
#define PAC5XXX_FLASH_SEG0_BASE                 (0x00000000UL)                              /*!< FLASH segment 0 Base Address         */
#define PAC5XXX_FLASH_SEG1_BASE                 (0x00000400UL)                              /*!< FLASH segment 1 Base Address         */
#define PAC5XXX_FLASH_SEG2_BASE                 (0x00000800UL)                              /*!< FLASH segment 2 Base Address         */
#define PAC5XXX_FLASH_SEG3_BASE                 (0x00000C00UL)                              /*!< FLASH segment 3 Base Address         */
#define PAC5XXX_FLASH_SEG4_BASE                 (0x00001000UL)                              /*!< FLASH segment 4 Base Address         */
#define PAC5XXX_FLASH_SEG5_BASE                 (0x00001400UL)                              /*!< FLASH segment 5 Base Address         */
#define PAC5XXX_FLASH_SEG6_BASE                 (0x00001800UL)                              /*!< FLASH segment 6 Base Address         */
#define PAC5XXX_FLASH_SEG7_BASE                 (0x00001C00UL)                              /*!< FLASH segment 7 Base Address         */
#define PAC5XXX_FLASH_SEG8_BASE                 (0x00002000UL)                              /*!< FLASH segment 8 Base Address         */
#define PAC5XXX_FLASH_SEG9_BASE                 (0x00002400UL)                              /*!< FLASH segment 9 Base Address         */
#define PAC5XXX_FLASH_SEG10_BASE                (0x00002800UL)                              /*!< FLASH segment 10 Base Address        */
#define PAC5XXX_FLASH_SEG11_BASE                (0x00002C00UL)                              /*!< FLASH segment 11 Base Address        */
#define PAC5XXX_FLASH_SEG12_BASE                (0x00003000UL)                              /*!< FLASH segment 12 Base Address        */
#define PAC5XXX_FLASH_SEG13_BASE                (0x00003400UL)                              /*!< FLASH segment 13 Base Address        */
#define PAC5XXX_FLASH_SEG14_BASE                (0x00003800UL)                              /*!< FLASH segment 14 Base Address        */
#define PAC5XXX_FLASH_SEG15_BASE                (0x00003C00UL)                              /*!< FLASH segment 15 Base Address        */
#define PAC5XXX_FLASH_SEG16_BASE                (0x00004000UL)                              /*!< FLASH segment 0 Base Address         */
#define PAC5XXX_FLASH_SEG17_BASE                (0x00004400UL)                              /*!< FLASH segment 1 Base Address         */
#define PAC5XXX_FLASH_SEG18_BASE                (0x00004800UL)                              /*!< FLASH segment 2 Base Address         */
#define PAC5XXX_FLASH_SEG19_BASE                (0x00004C00UL)                              /*!< FLASH segment 3 Base Address         */
#define PAC5XXX_FLASH_SEG20_BASE                (0x00005000UL)                              /*!< FLASH segment 4 Base Address         */
#define PAC5XXX_FLASH_SEG21_BASE                (0x00005400UL)                              /*!< FLASH segment 5 Base Address         */
#define PAC5XXX_FLASH_SEG22_BASE                (0x00005800UL)                              /*!< FLASH segment 6 Base Address         */
#define PAC5XXX_FLASH_SEG23_BASE                (0x00005C00UL)                              /*!< FLASH segment 7 Base Address         */
#define PAC5XXX_FLASH_SEG24_BASE                (0x00006000UL)                              /*!< FLASH segment 8 Base Address         */
#define PAC5XXX_FLASH_SEG25_BASE                (0x00006400UL)                              /*!< FLASH segment 9 Base Address         */
#define PAC5XXX_FLASH_SEG26_BASE                (0x00006800UL)                              /*!< FLASH segment 10 Base Address        */
#define PAC5XXX_FLASH_SEG27_BASE                (0x00006C00UL)                              /*!< FLASH segment 11 Base Address        */
#define PAC5XXX_FLASH_SEG28_BASE                (0x00007000UL)                              /*!< FLASH segment 12 Base Address        */
#define PAC5XXX_FLASH_SEG29_BASE                (0x00007400UL)                              /*!< FLASH segment 13 Base Address        */
#define PAC5XXX_FLASH_SEG30_BASE                (0x00007800UL)                              /*!< FLASH segment 14 Base Address        */
#define PAC5XXX_FLASH_SEG31_BASE                (0x00007C00UL)                              /*!< FLASH segment 15 Base Address        */

/* -----------------------------  MEMCTL_FLASHSTATUS  ----------------------------- */
#define MEMCTL_FLASHSTATUS_WRITE_Pos          0                                             /*!< MEMCTL FLASHSTATUS: WRITE Position      */
#define MEMCTL_FLASHSTATUS_WRITE_Msk          (0x01UL << MEMCTL_FLASHSTATUS_WRITE_Pos)      /*!< MEMCTL FLASHSTATUS: WRITE Mask          */
#define MEMCTL_FLASHSTATUS_PERASE_Pos         1                                             /*!< MEMCTL FLASHSTATUS: PERASE Position     */
#define MEMCTL_FLASHSTATUS_PERASE_Msk         (0x01UL << MEMCTL_FLASHSTATUS_PERASE_Pos)     /*!< MEMCTL FLASHSTATUS: PERASE Mask         */

/* -----------------------------  MEMCTL_FLASHWSTATE  ----------------------------- */
#define MEMCTL_FLASHWSTATE_WSTATE_Pos         0                                             /*!< MEMCTL FLASHWSTATE: WSTATE Position     */
#define MEMCTL_FLASHWSTATE_WSTATE_Msk         (0x03UL << MEMCTL_FLASHWSTATE_WSTATE_Pos)     /*!< MEMCTL FLASHWSTATE: WSTATE Mask         */

#define FLASH_LOCK_ALLOW_FLASHWRITE_KEY   0xAAAAAAAA          /*!< Allow write to any FLASH pages not protected by RW bits                  */
#define FLASH_LOCK_ALLOW_PERASE_KEY       0xA5A55A5A          /*!< Allow write to FLASHPERASE register to erase FLASH pages                 */
#define FLASH_LOCK_ALLOW_MPERASE_KEY      0xFACE1956          /*!< Allow write to FLASHMPERASE register to mass erase FLASH pages           */
#define FLASH_LOCK_ALLOW_FLASHDBG_KEY     0x06BD1556          /*!< Allow write to FLASHDBG register to allow SWR access at device reset     */
#define FLASH_LOCK_ALLOW_FLASHWSTATE_KEY  0x12345678          /*!< Allow write to FLASHWSTATE register to configure FLASH wait states       */
#define FLASH_LOCK_ALLOW_BWRITE_KEY  	  0xCA726B18		  /*!< Allow buffered write                                                     */

#define FLASH_CTL_READ_ACTIVE_BIT         0x00000010          /*!< FLASHCTL read active bit                                                 */
#define FLASH_CTL_WRITE_ACTIVE_BIT        0x00000020          /*!< FLASHCTL write active bit                                                */
#define FLASH_CTL_PERASE_ACTIVE_BIT       0x00000040          /*!< FLASHCTL page erase active bit                                           */
#define FLASH_CTL_MPERASE_ACTIVE_BIT      0x00000100          /*!< FLASHCTL mass page erase active bit                                      */

#define FLASH_DBG_SWR_POR_EN              0xFFFF              /*!< SWR signals enabled at POR                                               */
#define FLASH_DBG_SWR_POR_DIS             0x6969              /*!< SWR signals disabled at POR                                              */

typedef enum 
{
  FLASH_WSTATE_HCLK_LTE_25MHZ = 0,                            /*!< FLASHWSTATE value for HCLK <= 25MHz                                      */
  FLASH_WSTATE_25MHZ_LT_HCLK_LTE_50MHZ = 1,                   /*!< FLASHWSTATE value for 25MHz < HCLK <= 50MHz                              */
  FLASH_WSTATE_50MHZ_LT_HCLK_LTE_75MHZ = 2,                   /*!< FLASHWSTATE value for 50MHz < HCLK <= 75MHz                              */
  FLASH_WSTATE_75MHZ_LT_HCLK_LTE_100MHZ = 3,                  /*!< FLASHWSTATE value for 75MHz < HCLK <= 100MHz                             */
} MEMCTL_WaitState;

typedef struct
{
  /*!< FLASHLOCK: Offset: 0x0000   FLASH Lock Register                                           */
  __IO uint32_t FLASHLOCK;                   /*!< Lock value to allow FLASH modifications        */
  
  /*!< FLASHCTL: Offset: 0x0004   FLASH Control Register                                         */
  union 
  {
     __IO uint32_t w;

    struct 
    {
      __IO uint32_t s              : 16;
           uint32_t                : 16;
    };
    struct 
    {
	  __IO uint32_t b              : 8;
           uint32_t                : 24;
    };
    struct 
    {
      __I  uint32_t WRITE          : 1;   	    /*!< Buffered write active                          */
      __I  uint32_t PERASE         : 1;         /*!< Page erase active                              */
           uint32_t                : 30;
    };
  } FLASHCTL;
  
  /*!< FLASHPAGE: Offset: 0x0008   FLASH PAGE Register                                         */
  union 
  {
     __IO uint32_t w;

    struct 
    {
      __IO uint32_t s               : 16;
           uint32_t                 : 16;
    };
    struct 
    {
      __IO uint32_t b               : 8;
           uint32_t                 : 24;
    };
    struct 
    {
      __IO uint32_t PAGE            : 5;       /*!< FLASH page to select for erase                */
           uint32_t                 : 27;
  	};
  } FLASHPAGE;
  
  __I uint32_t RESERVED1[2];
  
  /*!< FLASHPERASE: Offset: 0x0014 FLASH page erase */
  __IO uint32_t FLASHPERASE;                 /*!< FLASH segment erase (1)                          */
  
  __I uint32_t RESERVED3[3];
  
  /*!< SWDACCESS:     Offset: 0x0024 FLASH lock debug register */
  struct 
  {
    __IO uint32_t VAL              : 16;      /*!< FLASH debug access value                     */
         uint32_t                  : 16;
  } SWDACCESS;
  
  /*!< FLASHWSTATE:  Offset: 0x0028 FLASH Wait state register */
  struct 
  {
    __IO uint32_t VAL              : 2;       /*!< FLASH wait state value                       */
         uint32_t                  : 30;
  } FLASHWSTATE;

  /*!< FLASHBWRITE:  Offset: 0x002C Buffered FLASH write                                        */
  __IO uint32_t FLASHBWRITE;

  /*!< FLASHBWDATA: Offset: 0x0030  Buffered FLASH write data									*/
  struct 
  {
	  __IO uint32_t DATA            : 16;		/*!< Data to write 								*/
	  __IO uint32_t ADDRESS			: 9;		/*!< Relative half-word address within page 	*/
	  __IO uint32_t PAGE			: 5;		/*!< page that contains data to write			*/
	       uint32_t                 : 2;
  } FLASHBWRITEDATA;
 
} PAC5XXX_MEMCTL_TypeDef;

// Methods

// This function indicates if a memory controller page erase operation is in progress
// return 0: Not in progress; non-zero: in progress
int pac5xxx_memctl_page_erase_active(void) 
{ 
	return PAC5XXX_MEMCTL->FLASHCTL.PERASE; 
}

// This function indicates if a memory controller buffered write operation is in progress
// return 0: Not in progress; non-zero: in progress
int pac5xxx_memctl_buffered_write_active(void) 
{ 
	return PAC5XXX_MEMCTL->FLASHCTL.WRITE; 
}

// This function performs an erase of the given FLASH page
// page 			Flash page to erase (0-31)
void pac5xxx_memctl_flash_page_erase( int page )
{
  PAC5XXX_MEMCTL->FLASHPAGE.PAGE = page;
  PAC5XXX_MEMCTL->FLASHPERASE = FLASH_LOCK_ALLOW_PERASE_KEY;
}

// This function prepares the system for writing data to either the INFO or FLASH areas
void pac5xxx_memctl_flash_write_prep(void) 
{ 
	PAC5XXX_MEMCTL->FLASHLOCK = FLASH_LOCK_ALLOW_FLASHWRITE_KEY; 
}

// This function configures SWR access during a power-on reset
// enabled 			1: SWR access at reset; 0: No SWR access at POR
void pac5xxx_memctl_flash_swr_enable_por(int enabled)
{
	PAC5XXX_MEMCTL->FLASHLOCK = FLASH_LOCK_ALLOW_FLASHDBG_KEY;
  	PAC5XXX_MEMCTL->SWDACCESS.VAL = enabled;
}

// This function configures the number of FLASH controller wait states
// wait_states 		The number of wait states (0-3)
void pac5xxx_memctl_wait_state(MEMCTL_WaitState wait_states)
{
	PAC5XXX_MEMCTL->FLASHLOCK = FLASH_LOCK_ALLOW_FLASHWSTATE_KEY;
  	PAC5XXX_MEMCTL->FLASHWSTATE.VAL = wait_states;
}

// This function starts a buffered write operation with the given data
// segment 			FLASH segment that contains the data to write
// address_offset 	The address offset of the data
// data 			The data to write
void pac5xxx_memctl_buffered_write( int segment, int address_offset, uint16_t data )
{
	PAC5XXX_MEMCTL->FLASHBWRITE = FLASH_LOCK_ALLOW_BWRITE_KEY;
	PAC5XXX_MEMCTL->FLASHBWRITEDATA.PAGE = segment;
	PAC5XXX_MEMCTL->FLASHBWRITEDATA.ADDRESS = address_offset;
	PAC5XXX_MEMCTL->FLASHBWRITEDATA.DATA = data;
}

#endif