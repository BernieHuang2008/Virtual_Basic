#include <iostream>
#include <fstream>
#include <cstdint>
#include <iomanip>
using namespace std;

#define AX registers_[0x00]
#define BP registers_[0x06]
#define EIP registers_[0x08]

enum Instructions
{
    HLT = 0x00,
    NOT = 0x01,
    XOR = 0x02,
    OR = 0x03,
    AND = 0x04,
    MOV = 0x05,
};

class VirtualProcessor
{
public:
/* Macro */
#define NEXT memory_[EIP++]
#define THIS memory_[EIP]
#define NEXT_REG THIS & 0xF0 ? reinterpret_cast<uint16_t *>(reinterpret_cast<uint8_t *>(&registers_[THIS & 0x0F]) + (NEXT & 0xF0) - 1) : &registers_[NEXT]
#define oper(total)                                                    \
    for (int i = 0; i < total; i++)                                    \
    op_type = NEXT,                                                    \
    operands[i] = (op_type == 0x00   ? &NEXT                           \
                   : op_type == 0x01 ? NEXT_REG                        \
                   : op_type == 0x02 ? &memory_[BP * 256 + NEXT]       \
                   : op_type == 0x03 ? new uint16_t(NEXT * 256 + NEXT) \
                                     : nullptr)

    /* ===== Macro END ===== */

    VirtualProcessor()
    {
        // init
        for (int i = 0; i < 16; i++)
        {
            registers_[i] = 0;
        }
        for (int i = 0; i < 65536; i++)
        {
            memory_[i] = 0;
        }
    }

    void LoadProgram(uint16_t entrance, const char *program, int size)
    {
        for (int i = 0; i < size; i++)
        {
            memory_[entrance + i] = static_cast<unsigned char>(program[i]);
        }
        delete[] program;
    }

    void Run(uint16_t entrance)
    {
        EIP = entrance;
        while (true)
        {
            uint16_t opcode = NEXT;
            uint16_t op_type;
            uint16_t *operands[3];

            // cout << "- pc:" << EIP - 1 << endl;

            switch (opcode)
            {
            case HLT:
                // std::cout << "HLT at " << EIP - 1 << std::endl;
                return;
            case NOT:
                oper(1);
                *operands[0] = ~*operands[0];
                break;
            case XOR:
                oper(2);
                *operands[0] ^= *operands[1];
                break;
            case OR:
                oper(2);
                *operands[0] |= *operands[1];
                break;
            case AND:
                oper(2);
                *operands[0] &= *operands[1];
                break;
            case MOV:
                // NEXT;
                // std::cout << "94:" << (NEXT & 0xF0) << endl;
                // EIP -= 2;
                oper(2);
                *operands[0] = *operands[1];
                break;
            default:
                std::cerr << "Invalid opcode: " << static_cast<int>(opcode) << " at " << EIP - 1 << std::endl;
                return;
            }
        }
    }

    void print_CGA()
    {
        std::cout << "------- CGA -------\n";
        for (int i = 0xA000; i < 0xBFFF; i++)
        {
            std::cout << static_cast<char>(memory_[i]);
        }
        std::cout << "\n------- CGA -------\n";
    }

    void dbg_print_mem(int start = 0, int end = 65536)
    {
        // border in grey
        for (int i = 0; i < 16; i++)
            std::cout << "====";
        cout << "\n\033[32m";
        for (int i = 0; i < 16; i++)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i) << "  ";
        }
        cout << "\033[0m" << endl;

        for (int i = start; i < end; i++)
        {
            if (i % 16 == 0)
                std::cout << std::endl;
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(memory_[i]) << "  ";
        }
        cout << endl;
        for (int i = 0; i < 16; i++)
            std::cout << "====";
        cout << endl;
    }

    void dbg_print_reg()
    {
        for (int i = 0; i < 16; i++)
        {
            std::cout << std::hex << std::setw(4) << std::setfill(' ') << static_cast<int>(registers_[i]) << "  ";
        }
        cout << endl;
    }

private:
    uint16_t registers_[16];
    uint16_t memory_[65536];
};

int main()
{
    ifstream file("output.bin", ios::binary);
    if (!file)
    {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    // 获取文件大小
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.seekg(0, ios::beg);

    // 读取文件内容到字节数组
    char *program = new char[size];
    file.read(program, size);

    VirtualProcessor vp;
    vp.LoadProgram(0, program, size);
    vp.Run(0);
    vp.print_CGA();
    vp.dbg_print_reg();
    return 0;
}
