# o01_utils
Dumps strings stored in .o01 string files used by some Qualcomm Brew applications.

Part of my long term project of studying/reverse enginnering flip phones.

Under brew, some programs store their strings in a ".o01" file. On the lg voyager, V CAST Music (verizonmediaplayer.mod) stores its strings in "vodstrings.o01".

In general the file structure is as follows:

struct header { int32_t total_string_count; int32_t total_string_length; } struct string { int32_t id; int32_t length; char str[]; }
