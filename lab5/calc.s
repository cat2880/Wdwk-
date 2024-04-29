EXIT_SUCCESS = 0
SYSEXIT = 1
.code32
.data

plusjeden: .float 1.0
minusjeden: .float -1.0
plusnull: .float 0.0
minusnull: .float -0.0
plusnieskonczonosc: .float 9.999999

.text

.global _start
_start:

# plus zero
flds plusnull

# minus zero
fldz
fchs

# plus nieskonczonosc
flds minusjeden
fdivs minusnull

# minus nieskonczonosc
flds plusjeden
fdivs plusnull
fchs

# not a number
flds minusnull
fdivs plusnull
fchs

mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
