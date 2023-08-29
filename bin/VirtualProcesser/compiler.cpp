#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

enum Instructions
{
    HLT = 0x00,
    NOT = 0x01,
    XOR = 0x02,
    OR = 0x03,
    AND = 0x04,
    MOV = 0x05,
    INT = 0x06,
    JMP = 0x07
};

map<string, int> opcodes = {
    {"NOT", NOT},
    {"XOR", XOR},
    {"OR", OR},
    {"AND", AND},
    {"MOV", MOV},
    {"INT", INT},
    {"JMP", JMP}};

int operand_num[] = {0, 1, 2, 2, 2, 2, 1, 1};

map<string, char> registers = {
    {"AX", 0x00},
    {"BX", 0x01},
    {"CX", 0x02},
    {"DX", 0x03},
    {"SI", 0x04},
    {"DI", 0x05},
    {"BP", 0x06},
    {"SP", 0x07},
    {"IP", 0x08},
    {"CS", 0x09},
    {"DS", 0x0A},
    {"ES", 0x0B},
    {"FS", 0x0C},
    {"GS", 0x0D},
    {"SS", 0x0E},
    {"FLAGS", 0x0F},
    {"AH", 0x10},
    {"AL", 0x20},
    {"BH", 0x11},
    {"BL", 0x21},
    {"CH", 0x12},
    {"CL", 0x22},
    {"DH", 0x13},
    {"DL", 0x23},
};

uint16_t todec(string operand)
{
    if (operand[0] == '0' && operand[1] == 'X' || operand[operand.length() - 1] == 'H')
    {
        return stoi(operand, nullptr, 16);
    }
    return stoi(operand, nullptr, 10);
}

uint8_t get_operand_type(string operand)
{
    if (operand[0] == '[') // memory
        return 0x02;
    if (registers.find(operand) != registers.end()) // register
        return 0x01;
    if (operand.find(":") != string::npos) // segment(reg) + offset
        return 0x04;
    if (todec(operand) <= 0xff) // short immidiate
        return 0x00;
    else // immidiate 16 bit
        return 0x03;
}

uint16_t tochar(string operand)
{
    int type = get_operand_type(operand);
    switch (type)
    {
    case 0x00: // immidiate
        return todec(operand);
    case 0x01: // register
        return registers[operand];
    case 0x02: // memory
        operand = operand.substr(1, operand.length() - 2);
        return tochar(operand);
    case 0x03: // immidiate 16 bit
        return todec(operand);
    case 0x04: // segment + offset
        return tochar(operand.substr(0, operand.find(":"))) * 256 + tochar(operand.substr(operand.find(":") + 1));
    default:
        cerr << "Invalid operand type: " << type << endl;
        return 0x00;
    }
}

#define OPERAND(total)                                                              \
    for (int i = 1; i <= total; i++)                                                \
    {                                                                               \
        uint16_t optype = get_operand_type(operand[i]), opval = tochar(operand[i]); \
        if (optype == 0x03)                                                   \
            printf("%c%c%c", optype, opval >> 8, opval);                            \
        else if (optype == 0x04)                                              \
            printf("%c%c%c", optype, opval >> 8, opval);                            \
        else                                                                        \
            printf("%c%c", optype, opval);                                          \
    }

int main(int argc, char *argv[])
{
    freopen("input.asm", "r", stdin);
    freopen("output.bin", "wb", stdout);

    // 循环读入，直到遇到 EOF
    while (!cin.eof())
    {
        string s;
        getline(cin, s);                                     // 读入一行
        transform(s.begin(), s.end(), s.begin(), ::toupper); // format: upper case

        string operand[4];
        int j = 0;
        char spliter = ' ';

        for (char c : s)
        {
            // comment
            if (c == ';')
                break;

            // split
            if (c == spliter)
                j++, spliter = ',';
            else if (c != ' ') // ignore space
                operand[j] += c;
        }

        // empty line
        if (j == 0)
            continue;

        // opcode
        string opcode = operand[0];
        cout << (char)opcodes[opcode];
        // operands
        OPERAND(operand_num[opcodes[opcode]]);
    } // end while

    cout << (char)HLT;
    return 0;
}
