#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

//Итоговая программа со структурами
/*
Везде использованы BYTE т.к. при использовании WORD или DWORD все перемешивается,
ну или по крайней мере идет не в том порядке как в структуре, например,
currentVolume->header_flags содержит байты размера заголовка и наоборот,
currentVolume->header_size содержит байты флагов, хотя первые поля структуры,
header_crc и header_type идут в том порядке, что и в объявлении структуры.
*/
using namespace std;

typedef struct
{
	BYTE header_crc[2];
	BYTE header_type;
	BYTE header_flags[2];
	BYTE header_size[2];


} RarVolumeHeaderFormat;

typedef struct
{
	BYTE PackSize[4];
	BYTE UnpSize[4];
	BYTE HostOS;
	BYTE FileCRC[4];
	BYTE FileTime[4];
	BYTE UnpVer;
	BYTE Method;
	BYTE NameSize[2];
	BYTE FileAttr[4];

} FileHead;


BYTE RarSig[7] = {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00};

void OglavStruct(vector<unsigned char> &dataBuffer, DWORD filesize)
{

    //Задаем отступ, изначально равен 7, т.к. пропустили сигнатуру
    uint32_t offset = sizeof(RarSig);

    uint16_t currentHeaderSize = 0;
    uint32_t currentPackSize = 0;
    uint16_t currentNameSize = 0;
    uint16_t numberOfFiles = 0;
    string currFileName = "";

    while(offset < filesize)
    {
        //Определяем указатель типа RarVolumeHeaderFormat на элемент dataBuffer, который является началом новой записи
        RarVolumeHeaderFormat *currentVolume = (RarVolumeHeaderFormat*)&dataBuffer[offset];

        //Выводим тип текущей записи
        cout << "Type: " << (int*)currentVolume->header_type << endl; //Приводим к типу указателя, чтобы получить вывод в 16-ричной СС

        //Текущий размер заголовка записи(без упакованных данных)
        currentHeaderSize = ((currentVolume->header_size[1]) << 8) +
                             (currentVolume->header_size[0]);

        //Дальше в зависимости от типа заголовка будут разные операции

        if(currentVolume->header_type == 0x73)
        {
            offset += currentHeaderSize; //Таким образом, если тип записи 0x73, то мы переходим к следующей
            cout << endl;
        }
        else if(currentVolume->header_type == 0x74)
        {
            numberOfFiles++;
            FileHead *currentFileVol = (FileHead*)&dataBuffer[offset+7];

            //Размер запакованных данных
            currentPackSize =((currentFileVol->PackSize[3]) << 24) +
                             ((currentFileVol->PackSize[2]) << 16) +
                             ((currentFileVol->PackSize[1]) << 8) +
                              (currentFileVol->PackSize[0]);

            //Размер имени
            currentNameSize = ((currentFileVol->NameSize[1]) << 8) +
                               (currentFileVol->NameSize[0]);

            //Собираем имя файла
            size_t BeginOfName = offset+sizeof(RarVolumeHeaderFormat)+sizeof(FileHead);
            size_t EndOfName = offset+sizeof(RarVolumeHeaderFormat)+sizeof(FileHead)+currentNameSize;
            currFileName = "";
            for(size_t i = BeginOfName; i != EndOfName; i++)
            {
                currFileName.push_back(dataBuffer[i]);
            }
            cout << "Name " << numberOfFiles << ": " << currFileName << endl;
            cout << "Packed data size: " << currentPackSize << endl;
            //Новый отступ, переход на другую запись
            offset += currentHeaderSize + currentPackSize;
            cout << endl;
        }
        //Заголовок типа ENDARC_HEAD
        else if(currentVolume->header_type == 0x7b)
        {
            cout << "It is file end\n" << endl;
            offset += currentHeaderSize;
        }
        //Для других типов записей
        else
        {
            offset += currentHeaderSize;
            cout << endl;
            continue;
        }
    }
    cout << "Total number of files: " << numberOfFiles << endl;
}

int main()
{
    HANDLE fileHandle = CreateFile("Example.rar", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(fileHandle == INVALID_HANDLE_VALUE)
    {
        cout << "Opening error!"<< endl;
    }


    DWORD fileSize = GetFileSize(fileHandle, NULL);

    vector<unsigned char> dataBuffer(fileSize);


    DWORD bytesRead;
    bool readOk = ReadFile(
            fileHandle,
            &dataBuffer[0],
            fileSize,
            &bytesRead,
            NULL
            );
    if(readOk)
    {
        cout << "File is read" << "\n\n";

        OglavStruct(dataBuffer, fileSize);

        dataBuffer.clear();
    }

    bool closed = CloseHandle(fileHandle);
    if(closed)
    {
        cout << "\n\nFile closed" << endl;
    }

}
