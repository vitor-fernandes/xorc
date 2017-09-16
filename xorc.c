#include <stdio.h>
#include <string.h>

void menu()
{
	printf("\n██╗  ██╗ ██████╗ ██████╗  ██████╗");
	printf("\n╚██╗██╔╝██╔═══██╗██╔══██╗██╔════╝");
	printf("\n ╚███╔╝ ██║   ██║██████╔╝██║     ");
	printf("\n ██╔██╗ ██║   ██║██╔══██╗██║     ");
	printf("\n██╔╝ ██╗╚██████╔╝██║  ██║╚██████╗");
	printf("\n╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝\n");                              
}	

int help() // Função que mostra como se usa o script
{
	printf("\nUSAGE: \n\tEncrypt: ./xorc key file output\n\tDecrypt: ./xorc key encrypted output\n");
	return 1;
}

int errors() // Função que mostra quais são os possíveis erros na execução do script
{
	printf("\n[!] POSSIBLE ERRORS [!]\n\n");
	printf("You Don't Have Permissions\n");
	printf("The Files Doesn't Exists\n\n");
	return 1;
}

int main(int args, char *argvs[])
{
	FILE *file, *encryptedFile; // Ponteiro do tipo FILE para receber os arquivos 
	int caractere; // Variável que recebe cada caractere do arquivo
	char *password; // Ponteiro do tipo char que recebe a keyword
	
	password = argvs[1];
	
	if (args < 4) // Se o usuário executar o script faltando algum argumento, receberá uma mensagem
	{
		menu();
		help();
		return 1;
	}
	
	else
	{
		menu();
		printf("\n[+] WORKING WITH FILE: %s [+]\n\n", argvs[2]);
		if (*password != '\0') // Verifica se a chave não está em branco
		{
			file = fopen(argvs[2],"rb"); // Abre o primeiro arquivo passado 
			if (file != NULL) // Verifica se o arquivo existe ou se tem permissão de leitura
			{
				encryptedFile = fopen(argvs[3], "wb"); // Cria/Abre o segundo arquivo passado
				if (encryptedFile != NULL) // Verifica se o arquivo existe ou se tem permissão de escrita
				{
					while ((caractere = getc(file)) != EOF) // Vai varrer todos os caracteres até encontrar o final do arquivo
					{	
						if (!*password) password = argvs[1]; // Se não houver keyword, será atribuída novamente pelo argvs
						
						caractere ^= *(password++); // O caractere vai ser encriptado com o XOR de acordo com a keyword que foi digitada
						putc(caractere, encryptedFile); // A função putc vai gravar todos os caracteres mudados com o XOR no arquivo
					}
					printf("[*] DONE [*]\n");
					printf("\nFile Output: %s\n\n", argvs[3]);
					fclose(encryptedFile); // Fecha o arquivo final
				}
				
				else
				{
					errors(); 
				}
				
				fclose(file); // Fecha o arquivo inicial
			}
			
			else
			{
				errors();
			}
		}
		else
		{
			errors();
		}
	}
	return 0; // Retorna 0 se o script for executado sem erro
}
