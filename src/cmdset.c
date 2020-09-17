#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void cmdset(FILE *file_in, FILE *file_out, int text_speed, int window_id){
    fseek(file_in, 0, SEEK_END);
    size_t length = ftell(file_in);
    fseek(file_in, 0, SEEK_SET);

    char *file_content;

    file_content = calloc(length, sizeof(char));
    fread(file_content, sizeof(char), length, file_in);

    // start first command
    fprintf(file_out, "#!/bin/bash\n\n");
    fprintf(file_out, "xdotool key --window %d --delay %d ",
            window_id, text_speed);
    for (size_t i = 0; i < length; ++i){
        switch(file_content[i]){
            case '\n':
                fprintf(file_out, "Return\n");
                fprintf(file_out, "read -p 'Press enter to continue'\n");
                fprintf(file_out, "xdotool key --window %d --delay %d ",
                        window_id, text_speed);
                break;
            case '?':
                fprintf(file_out, "question ");
                break;
            case '!':
                fprintf(file_out, "exclam ");
                break;
            case ' ':
                fprintf(file_out, "space ");
                break;
            case '\\':
                if (i+3 < length && strncmp(&file_content[i+1], "ESC", 3) == 0){
                    fprintf(file_out, "0xff1b ");
                    i+=3;
                }
                else {
                    fprintf(file_out, "0x005c ");
                }
                break;

            default:
                fprintf(file_out, "%c ", file_content[i]);
                break;
        }

    }

    fclose(file_in);
    fclose(file_out);

}

int main(int argc, char* argv[]){
    int opt; 

    int window_id = -1, text_speed = 100;
    char *filename_in, *filename_out;
      
    while((opt = getopt(argc, argv, ":i:o:t:w:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'i':  
                printf("input filename: %s\n", optarg);  
                filename_in = optarg;
                break;  
            case 'o':  
                printf("output filename: %s\n", optarg);  
                filename_out = optarg;
                break;  
            case 't':  
                printf("text speed: %s\n", optarg);  
                text_speed = atoi(optarg);
                break;  
            case 'w':  
                printf("window ID: %s\n", optarg);  
                window_id = atoi(optarg);
                break;  
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }  
      
    for(; optind < argc; optind++){      
        printf("extra arguments: %s\n", argv[optind]);  
    } 

    FILE *file_in = fopen(filename_in, "r");
    FILE *file_out = fopen(filename_out, "w");

    if (file_in != NULL && file_out != NULL){
        cmdset(file_in, file_out, text_speed, window_id);
    }
    else {
        fprintf(stderr, "Error opening file!");
    }

    return 0; 
}
