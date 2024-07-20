#include<stdio.h>
#include<elf.h>
#include"function.h"
int expected_salary =5000;
int real_salary ;
const int increasing;


void print_elf_header_info(const Elf64_Ehdr *ehdr) {
    printf("ELF Header:\n");
    printf("  Magic:                             ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", ehdr->e_ident[i]);
    }
    printf("\n");

    printf("  Class:                             ");
    switch (ehdr->e_ident[EI_CLASS]) {
        case ELFCLASS32: printf("ELF32\n"); break;
        case ELFCLASS64: printf("ELF64\n"); break;
        default: printf("Unknown\n"); break;
    }

    printf("  Data:                              ");
    switch (ehdr->e_ident[EI_DATA]) {
        case ELFDATA2LSB: printf("2's complement, little endian\n"); break;
        case ELFDATA2MSB: printf("2's complement, big endian\n"); break;
        default: printf("Unknown\n"); break;
    }

    printf("  Version:                           %d (current)\n", ehdr->e_ident[EI_VERSION]);

    printf("  OS/ABI:                            ");
    switch (ehdr->e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
        case ELFOSABI_LINUX: printf("Linux\n"); break;
        default: printf("Unknown (0x%x)\n", ehdr->e_ident[EI_OSABI]); break;
    }

    printf("  ABI Version:                       %d\n", ehdr->e_ident[EI_ABIVERSION]);

    printf("  Type:                              ");
    switch (ehdr->e_type) {
        case ET_NONE: printf("No file type\n"); break;
        case ET_REL: printf("Relocatable file\n"); break;
        case ET_EXEC: printf("Executable file\n"); break;
        case ET_DYN: printf("Shared object file\n"); break;
        case ET_CORE: printf("Core file\n"); break;
        default: printf("Unknown (0x%x)\n", ehdr->e_type); break;
    }

    printf("  Machine:                           ");
    switch (ehdr->e_machine) {
        case EM_X86_64: printf("AMD x86-64\n"); break;
        case EM_386: printf("Intel 80386\n"); break;
        case EM_ARM: printf("ARM\n"); break;
        default: printf("Unknown (0x%x)\n", ehdr->e_machine); break;
    }

    printf("  Version:                           0x%x\n", ehdr->e_version);

    printf("  Entry point address:               0x%lx\n", ehdr->e_entry);
    printf("  Start of program headers:          %lu (bytes into file)\n", ehdr->e_phoff);
    printf("  Start of section headers:          %lu (bytes into file)\n", ehdr->e_shoff);
    printf("  Flags:                             0x%x\n", ehdr->e_flags);
    printf("  Size of this header:               %d (bytes)\n", ehdr->e_ehsize);
    printf("  Size of program headers:           %d (bytes)\n", ehdr->e_phentsize);
    printf("  Number of program headers:         %d\n", ehdr->e_phnum);
    printf("  Size of section headers:           %d (bytes)\n", ehdr->e_shentsize);
    printf("  Number of section headers:         %d\n", ehdr->e_shnum);
    printf("  Section header string table index: %d\n", ehdr->e_shstrndx);
}
	
int main (int ,char **arch)
{
	 Elf64_Ehdr header;

	FILE *file = fopen( arch[1],"r"  );
	 fread(&header,1, sizeof(header), file);
         fclose(file);
	 print_elf_header_info(&header);

// printing elf data

/*

  printf("please enter your expected salary\n");
  scanf("%d",&expected_salary);

  printf("please enter your real salary\n");
  scanf("%d",&real_salary);
  print_data(expected_salary,real_salary,increasing);
  */
  return 0;

}

 