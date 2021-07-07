// Project.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <windows.h>
#include <WinBase.h>
#include <iostream>
#include <string>

DCB dcb;
void* hCom;
int Success;

void GetLastErrorAsString()
{
    unsigned long errorMessageID = GetLastError();
    if (errorMessageID == 0) 
    {
       return; //No error message has been recorded
    }

    char* messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
    printf("%s", message);
     //std::cout << message;
}

void PrintComState(DCB* dcb)
{
     printf("BaudRate %d, ByteSyze %d, Parity %d\n", dcb->BaudRate, (unsigned int)dcb->ByteSize, (unsigned int)dcb->Parity);
   // std:: cout << "BaudRate " << dcb-> BaudRate <<"  ByteSyze " << (unsigned int) dcb->ByteSize << "  Parity " <<(unsigned int) dcb->Parity;
   //  std::cout << std::endl;
}

void SetOnCons(DCB* dcb)
{
       dcb->BaudRate = CBR_115200;     //  baud rate 
       dcb->ByteSize = 8;              //  data size, xmit and rcv
       dcb->Parity = NOPARITY;         //  parity bit
}

 
void ReadCOM(uint8_t* buf)
{
    unsigned long  iSize;
    int sReceivedChar;

    while (true)
    { 

       bool read = ReadFile(hCom, buf, 64, &iSize, 0);

        if (iSize > 64)
        {
            iSize = 64;
        }
        for (int i = 0; i < iSize; i++)
        {
            printf("%X\n", buf[i]);
            // std::cout << (int)buf[i] << std::endl;
        }
    }
}

//uint16_t Crc16(uint8_t* pcBlock, uint8_t len) // hyetaaaaaaaaaaaaaaa
//{
//    /*
//      Name  : CRC-16 CCITT
//      Poly  : 0x1021    x^16 + x^12 + x^5 + 1
//      Init  : 0xFFFF
//      Revert: false
//      XorOut: 0x0000
//      Check : 0x29B1 ("123456789")
//      MaxLen: 4095 байт (32767 бит) - обнаружение
//          одинарных, двойных, тройных и всех нечетных ошибок
//    */
//    uint16_t crc = 0xFFFF;
//    uint16_t pcBlock;
//
//    while (len--)
//    {
//        crc ^= *pcBlock++ << 8;
//
//        for (uint8_t i = 0; i < 8; i++)
//            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
//    }
//    return crc;
//}



uint32_t ID_MC = 0xFFFFFFFF;
uint32_t ID_PC = 0xAAAAAAAA;

struct Data_packet
{
    uint32_t ID_sender;
    uint32_t ID_receiver;
    uint32_t ID_packet;
    uint32_t length_message;
    uint8_t data[46];
    uint32_t checksum;
} data_packet;


int main(int argc, TCHAR* argv[])
{
    uint8_t buf[64] = { 0 };

    const wchar_t* pcCommPort = TEXT("\\\\.\\COM8");
    hCom = CreateFile(pcCommPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); 

    if (hCom == INVALID_HANDLE_VALUE)
    {
        //  Handle the error.
        GetLastErrorAsString();
        return (1);
    }

    //  Initialize the DCB structure.
    SecureZeroMemory(&dcb, sizeof(DCB)); //     Pointer to the DCB to be filled with zero
    dcb.DCBlength = sizeof(DCB);         //     returns the length in bytes

    //  Build on the current configuration by first retrieving all current
    //  settings.

    Success = GetCommState(hCom, &dcb);

    if (!Success)
    {
        printf("GetCommState failed with error %d.\n", GetLastError());
        return (2);
    }

    SetOnCons(&dcb);
    PrintComState(&dcb); //  Output to consol
    SetCommState(hCom, &dcb);
   
    Success = GetCommState(hCom, &dcb);

    if (!Success)
    {
        printf("GetCommState failed with error %d.\n", GetLastError());
        return (2);
    }
    ReadCOM(buf);

    data_packet.ID_sender = buf[3] | buf[2] << 8 | buf[1] << 16 | buf[0] << 24;
    data_packet.ID_receiver = buf[7] | buf[6] << 8 | buf[5] << 16 | buf[4] << 24;
    data_packet.ID_packet = buf[11] | buf[10] << 8 | buf[9] << 16 | buf[8] << 24;
    data_packet.length_message = buf[15] | buf[14] << 8 | buf[13] << 16 | buf[12] << 24;
    data_packet.checksum = buf[63] | buf[62] << 8;

    for (int k = 16; k < 62; k++)
    {
        data_packet.data[k - 16] = buf[k];
    }

   /* uint16_t checksum = Crc16(&buf[64], 64);*/

   /* if ()
    {
    }*/
}






