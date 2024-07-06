import math

def main():
    for i in range(0, 64):
        val = (1 << 32) * abs(math.sin(i + 1))
        print(f'0x{int(val):x}')

if __name__ == '__main__':
    main()