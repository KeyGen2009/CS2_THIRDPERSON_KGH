#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <conio.h>


using namespace std;

#define VK_T 0x54

//Variables del proceso
DWORD pid;
HANDLE hp;


//Headers para el cheat
#include "KGModulos.h"

//Modulos del juego
ModuloInfo CLIENT;

//Thirdperson hack
uintptr_t PARCHE_THIRDPERSON = 0xACB581;
unsigned char parche_thirdperson[] = { 0x75,0x66 };

uintptr_t ACTIVADOR_THIRDPERSON = 0x23562E8;
int activador_thirdperson_on = 256;
int activador_thirdperson_off = 0;


int main()
{
	//Abrimos el proceso
	hp = kg_abrir_proceso("cs2.exe", PROCESS_ALL_ACCESS);

	//Cargamos los modulos del proceso
	CLIENT = kg_obtener_modulo_info(pid, L"client.dll");

	//Parchear instruccion
	WriteProcessMemory(hp, (LPBYTE)(CLIENT.base + PARCHE_THIRDPERSON), &parche_thirdperson, sizeof(parche_thirdperson), 0);

	while (1)
	{
		if (GetKeyState(VK_T))
		{
			WriteProcessMemory(hp, (LPBYTE)(CLIENT.base + ACTIVADOR_THIRDPERSON), &activador_thirdperson_on, sizeof(activador_thirdperson_on), 0);
		}
		else {
			WriteProcessMemory(hp, (LPBYTE)(CLIENT.base + ACTIVADOR_THIRDPERSON), &activador_thirdperson_off, sizeof(activador_thirdperson_off), 0);

		}
		Sleep(1);
	}
	

}