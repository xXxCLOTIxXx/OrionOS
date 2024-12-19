#include <include/multiboot.h>
#include <include/video/vbe.h>
#include <kernel/kernel.h>
#include <include/mem.h>
#include <kernel/klog/log.h>
#include <include/video/vbe_text.h>
#include <include/video/vga_tm.h>
#include <include/io.h>
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))


void loop(){
    while (1)
    {
        __asm__("hlt");
    }
    
}


void cmain (unsigned long addr, unsigned long magic)
{
  multiboot_info_t *mbi;
  tm_vga_clear();
  tm_vga_printf("Booting...\n");

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      tm_vga_printf("BOOT ERROR: MULTIBOOT_BOOTLOADER_MAGIC error: 0x%x", (unsigned) magic);
      loop();
    }
  mbi = (multiboot_info_t *) addr;
  tm_vga_printf("flags = 0x%x\n", (unsigned) mbi->flags);

  if (CHECK_FLAG (mbi->flags, 4) && CHECK_FLAG (mbi->flags, 5)){
      tm_vga_printf("BOOT ERROR: Both bits 4 and 5 are set.\n");
      loop();
  }
  if (CHECK_FLAG (mbi->flags, 0)){
    tm_vga_printf("mem_lower = %uKB, mem_upper = %uKB\n", (unsigned) mbi->mem_lower, (unsigned) mbi->mem_upper);
  }
  if (CHECK_FLAG (mbi->flags, 1)){
    tm_vga_printf("boot device = 0x%x\n", (unsigned) mbi->boot_device);
  }


  if (CHECK_FLAG (mbi->flags, 6))
    {
    mem_init(mbi);
  } else{
    tm_vga_printf("BOOT ERROR: mmap not supported.");
    loop();
  }

    if (!(mbi->flags & (1 << 11)) || !mbi->vbe_control_info || !mbi->vbe_mode_info) {
        tm_vga_printf("BOOT ERROR: vesa (vbe) not supported");
        loop();
  }
  //set_vesa_mode();
  vbe_init(mbi);
  clear();
  LOG_OK("vbe init.");
  LOG_OK("mem init.");
  int result = kernel(mbi);
  if (result == 1){
    outb(0x64, 0xFE); 
  }

}
