/******************************************************************************
 * File:       /vv4os/stdlib/stdio.c                                          *
 * Author:     vodozhaba                                                      *
 * Created on: Aug 21, 2016                                                   *
 * Purpose:    Provides standard I/O functions.                               *
 ******************************************************************************/

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include "io/vga_terminal.h"
#include "stdlib/stdio.h"
#include "stdlib/stdlib.h"
#include "stdlib/string.h"

int putchar(int character) {
    VgaTerminalPut((char) character);
    return character;
}

int _puts(const char* s) {
    for(size_t i = 0; s[i] != 0x00; ++i) {
        int res = putchar(s[i]);
        if(res != 0)
            return res;
    }
    return 0;
}

int isspace (int c) {
	return strchr(" \t\n\v\f\r", c) != NULL;
}

int printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    for(size_t i = 0; fmt[i]; i++) {
        if(fmt[i] != '%') {
            putchar(fmt[i]);
            continue;
        }
        size_t width = 0;
        char c, pad_c = ' ';
    next:
        c = fmt[++i];
        switch(c) {
        case '0': {
			pad_c = '0';
			goto next; // sorry!
        }
    	case '1':
    	case '2':
    	case '3':
    	case '4':
    	case '5':
    	case '6':
    	case '7':
    	case '8':
    	case '9': {
    		width = atoi(&fmt[i]);
    		goto next;
    	}
        case '%': {
            putchar('%');
            break;
        }
        case 'd':
        case 'i': {
            int arg = va_arg(args, int);
            char str[32];
            itoa(arg, str, 10);
            size_t len = strlen(str);
            if(len < width) {
            	for(size_t k = 0; k < width - len; k++) {
            		putchar(pad_c);
            	}
            }
            puts(str);
            break;
        }
        case 'u': {
            unsigned int arg = va_arg(args, unsigned int);
            char str[32];
            utoa(arg, str, 10);
            size_t len = strlen(str);
            if(len < width) {
            	for(size_t k = 0; k < width - len; k++) {
            		putchar(pad_c);
            	}
            }
            puts(str);
            break;
        }
        case 'o': {
            unsigned int arg = va_arg(args, unsigned int);
            char str[32];
            utoa(arg, str, 8);
            size_t len = strlen(str);
            if(len < width) {
            	for(size_t k = 0; k < width - len; k++) {
            		putchar(pad_c);
            	}
            }
            puts(str);
            break;
        }
        case 'x': {
            unsigned int arg = va_arg(args, unsigned int);
            char str[32];
            utoa_lc(arg, str, 16);
            size_t len = strlen(str);
            if(len < width) {
            	for(size_t k = 0; k < width - len; k++) {
            		putchar(pad_c);
            	}
            }
            puts(str);
            break;
        }
        case 'X': {
            unsigned int arg = va_arg(args, unsigned int);
            char str[32];
            utoa(arg, str, 16);
            size_t len = strlen(str);
            if(len < width) {
            	for(size_t k = 0; k < width - len; k++) {
            		putchar(pad_c);
            	}
            }
            puts(str);
            break;
        }
        case 'c': {
            char arg = va_arg(args, int);
            putchar(arg);
            break;
        }
        case 's': {
            char* str = va_arg(args, char*);
            size_t len = strlen(str);
            if(len < width) {
            	for(size_t k = 0; k < width - len; k++) {
            		putchar(pad_c);
            	}
            }
            puts(str);
            break;
        }
    }
    }
    va_end(args);
    /* TODO add valid return value */
    return 0;
}

int sprintf(char* dest, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t j = 0;
    for(size_t i = 0; fmt[i]; i++) {
        if(fmt[i] != '%') {
            dest[j++] = fmt[i];
            continue;
        }
        size_t width = 0;
        char c, pad_c = ' ';
    next:
        c = fmt[++i];
        switch(c) {
        	case '0':
        		pad_c = '0';
        		goto next; // sorry!
        	case '1':
        	case '2':
        	case '3':
        	case '4':
        	case '5':
        	case '6':
        	case '7':
        	case '8':
        	case '9':
        		width = atoi(&fmt[i]);
        		goto next;
            case '%': {
                dest[j++] = '%';
                break;
            }
            case 'd':
            case 'i': {
                int arg = va_arg(args, int);
                char str[32];
                itoa(arg, str, 10);
                size_t len = strlen(str);
                if(len < width) {
                	for(size_t k = 0; k < width - len; k++) {
                		dest[j++] += pad_c;
                	}
                }
                strcpy(&dest[j], str);
                j += strlen(str);
                break;
            }
            case 'u': {
                unsigned int arg = va_arg(args, unsigned int);
                char str[32];
                utoa(arg, str, 10);
                size_t len = strlen(str);
                if(len < width) {
                	for(size_t k = 0; k < width - len; k++) {
                		dest[j++] += pad_c;
                	}
                }
                strcpy(&dest[j], str);
                j += strlen(str);
                break;
            }
            case 'o': {
                unsigned int arg = va_arg(args, unsigned int);
                char str[32];
                utoa(arg, str, 8);
                size_t len = strlen(str);
                if(len < width) {
                	for(size_t k = 0; k < width - len; k++) {
                		dest[j++] += pad_c;
                	}
                }
                strcpy(&dest[j], str);
                j += strlen(str);
                break;
            }
            case 'x': {
                unsigned int arg = va_arg(args, unsigned int);
                char str[32];
                utoa_lc(arg, str, 16);
                size_t len = strlen(str);
                if(len < width) {
                	for(size_t k = 0; k < width - len; k++) {
                		dest[j++] += pad_c;
                	}
                }
                strcpy(&dest[j], str);
                j += strlen(str);
                break;
            }
            case 'X': {
                unsigned int arg = va_arg(args, unsigned int);
                char str[32];
                utoa(arg, str, 16);
                size_t len = strlen(str);
                if(len < width) {
                	for(size_t k = 0; k < width - len; k++) {
                		dest[j++] += pad_c;
                	}
                }
                strcpy(&dest[j], str);
                j += strlen(str);
                break;
            }
            case 'c': {
                char arg = va_arg(args, int);
                dest[j++] = arg;
                break;
            }
            case 's': {
                char* str = va_arg(args, char*);
                size_t len = strlen(str);
                if(len < width) {
                	for(size_t k = 0; k < width - len; k++) {
                		dest[j++] += pad_c;
                	}
                }
                strcpy(&dest[j], str);
                j += strlen(str);
                break;
            }
        }
    }
    dest[j] = 0;
    va_end(args);
    return strlen(dest);
}