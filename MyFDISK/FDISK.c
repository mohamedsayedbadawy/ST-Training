#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>

typedef struct {
    uint8_t status;
    uint8_t first_chs[3];
    uint8_t partition_type;
    uint8_t last_chs[3];
    uint32_t lba;
    uint32_t sector_count;
} PartitionEntry;

void extended_partition( PartitionEntry *ex_part,int counter,int ex_fd,char **argv);
int main(int argc, char **argv)
{
    char buf[512];

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1 || read(fd, buf, 512) == -1) {
        perror("error in opening or reading file");
        return 1;
    }

    PartitionEntry *table_entry_ptr = (PartitionEntry *)&buf[446];

    printf("%-5s   %-10s%-10s %-10s %-10s %-10s %-10s %-10s\n", "Device",
           "Boot", "Start", "End", "Sectors", "Size (GB)", "Id", "Type");

    for (int i = 0; i < 4; i++) {
          
        // Calculate size in GB using float precision
        float size_gb = (float)table_entry_ptr[i].sector_count * 512.0f / (1024 * 1024 * 1024);
        
        // Apply ceil to round up the value and cast it to int
        int size_gb_int = (int)ceil(size_gb);

     //check if the partition is empty or not 
          if (size_gb_int==0)
             {
                continue;
              }


        // Print the size as an integer
        printf("%s%-5d %-5c %-9u %-10u %-10u %-10d %-10X\n",
               argv[1],
               i + 1,
               table_entry_ptr[i].status == 0x80 ? '*' : ' ',
               table_entry_ptr[i].lba,
               table_entry_ptr[i].lba + table_entry_ptr[i].sector_count - 1,
               table_entry_ptr[i].sector_count,
               size_gb_int,  // Print the size rounded up as an integer
               table_entry_ptr[i].partition_type);

              //check this desk is extended 
              if(table_entry_ptr[i].partition_type==5)
                {
                  extended_partition(table_entry_ptr,i,fd,argv);
                  }


    }

    close(fd);
    return 0;
}
//function to do extended partition 
void extended_partition( PartitionEntry *ex_part,int counter,int ex_fd,char **argv)
{
     // save the start of extended disk 
      static int temp =-1;
      static long long disk_start= 0;
      if (temp==-1)
    {   
            disk_start= ex_part[counter].lba*512;
            temp =0;
      }

     static int num_exDisk=5;
     char ex_buffer[512];

    //jump to certain extended disk
     if(lseek(ex_fd,(disk_start),SEEK_SET)==-1)
      {
         perror("there is error in leseek of first EBR");
        }

        if (read(ex_fd, ex_buffer, 512) == -1)
      { 
          perror("error in saving data in buffer");
        }


       //return ex_fd to its original state
      if (lseek(ex_fd,0,SEEK_SET)==-1)
       {
            perror("there is error in restore ex_fd");
         }
   PartitionEntry *copy_ex_part= (PartitionEntry *)&ex_buffer[446];
  


//print information about first logical partitionn

      // Calculate size in GB using float precision
        float ex_size_gb = (float)copy_ex_part[0].sector_count * 512.0f / (1024 * 1024 * 1024);
        
      // Apply ceil to round up the value and cast it to int
        int ex_size_gb_int = (int)ceil(ex_size_gb);

     //check if the partition is empty or not 
          if (ex_size_gb_int==0)
             {
              return ;
              }  
             else 
     {
               
       // Print the size as an integer
        printf("%s%-5d %-5c %-9u %-10u %-10u %-10d %-10X\n",
               argv[1],
               (num_exDisk++)+ 1,
               copy_ex_part[0].status == 0x80 ? '*' : ' ',
               copy_ex_part[0].lba,
               copy_ex_part[0].lba +  copy_ex_part[0].sector_count - 1,
               copy_ex_part[0].sector_count,
               ex_size_gb_int,  // Print the size rounded up as an integer
               copy_ex_part[0].partition_type);
   }

              //check this desk is extended 
              if(copy_ex_part[1].partition_type==5)
                {  

                  disk_start=(disk_start/512)+2048+(copy_ex_part[0].lba +  copy_ex_part[0].sector_count - 1);
                  extended_partition(copy_ex_part,1,ex_fd,argv);
                  }
                else
                {
                    return ;
                  }


            }



