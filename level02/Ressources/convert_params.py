import sys

str = '0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d'

for part in str.split('0x'):
    sys.stdout.write(part.decode('hex')[::-1])
print
