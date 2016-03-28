#ifndef _SYSTEM_H_
#define _SYSTEM_H_

typedef int size_t;

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

/* COMMON.C */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern int strcmp(char *str1, char *str2);
extern char *strcpy(char *dest, const char *src);
extern char *strcat(char *dest, const char *src);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern unsigned short inportw(unsigned short port);
extern void outportb (unsigned short _port, unsigned char _data);

/* SCRN.C */
extern void init_video(void);
extern void puts(unsigned char *text);
extern void putc(unsigned char c);
extern void cls();

/* GDT.C */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void timer_wait(int ticks);
extern void timer_install();
extern void timer_test(int count);

/* KEYBOARD.C */
extern void keyboard_install();

/* ORDERED_ARRAY.C */
typedef char (*lessthan_predicate_t)(void* ,void* );
typedef struct
{
    void*  *array;
    unsigned int size;
    unsigned int max_size;
    lessthan_predicate_t less_than;
} ordered_array_t;
extern char standard_lessthan_predicate(void*  a, void*  b);
extern ordered_array_t create_ordered_array(unsigned int max_size, lessthan_predicate_t less_than);
extern ordered_array_t place_ordered_array(void *addr, unsigned int max_size, lessthan_predicate_t less_than);
extern void destroy_ordered_array(ordered_array_t *array);
extern void insert_ordered_array(void*  item, ordered_array_t *array);
extern void*  lookup_ordered_array(unsigned int i, ordered_array_t *array);
extern void remove_ordered_array(unsigned int i, ordered_array_t *array);

/* KHEAP.C*/
#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000

#define HEAP_INDEX_SIZE   0x20000
#define HEAP_MAGIC        0x123890AB
#define HEAP_MIN_SIZE     0x70000
typedef struct
{
    unsigned int magic;   // Magic number, used for error checking and identification.
    unsigned char is_hole;   // 1 if this is a hole. 0 if this is a block.
    unsigned int size;    // size of the block, including the end footer.
} header_t;

typedef struct
{
    unsigned int magic;     // Magic number, same as in header_t.
    header_t *header; // Pointer to the block header.
} footer_t;

typedef struct
{
    ordered_array_t index;
    unsigned int start_address; // The start of our allocated space.
    unsigned int end_address;   // The end of our allocated space. May be expanded up to max_address.
    unsigned int max_address;   // The maximum address the heap can be expanded to.
    unsigned char supervisor;     // Should extra pages requested by us be mapped as supervisor-only?
    unsigned char readonly;       // Should extra pages requested by us be mapped as read-only?
} heap_t;
extern heap_t *create_heap(unsigned int start, unsigned int end, unsigned int max, unsigned char supervisor, unsigned char readonly);
extern void *alloc(unsigned int size, unsigned char page_align, heap_t *heap);
extern void free(void *p, heap_t *heap);
extern unsigned int kmalloc_int(unsigned int sz, int align, unsigned int *phys);
extern unsigned int kmalloc_a(unsigned int sz);
extern unsigned int kmalloc_p(unsigned int sz, unsigned int *phys);
extern unsigned int kmalloc_ap(unsigned int sz, unsigned int *phys);
extern unsigned int kmalloc(unsigned int sz);
extern void kfree(void *p);


/* PAGING.C */
typedef struct page
{
    unsigned int present    : 1;   // Page present in memory
    unsigned int rw         : 1;   // Read-only if clear, readwrite if set
    unsigned int user       : 1;   // Supervisor level only if clear
    unsigned int accessed   : 1;   // Has the page been accessed since last refresh?
    unsigned int dirty      : 1;   // Has the page been written to since last refresh?
    unsigned int unused     : 7;   // Amalgamation of unused and reserved bits
    unsigned int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    page_table_t *tables[1024];
    unsigned int tablesPhysical[1024];
    unsigned int physicalAddr;
} page_directory_t;
extern void paging_install();
extern void switch_page_directory(page_directory_t *new);
extern page_t *get_page(unsigned int address, int make, page_directory_t *dir);
extern void page_fault(struct regs *regs);
extern page_directory_t *clone_directory(page_directory_t *src);
page_directory_t *kernel_directory=0;
page_directory_t *current_directory=0;

#endif
