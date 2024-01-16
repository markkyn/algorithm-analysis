import random

def criar_arquivo_vetores_desordenados(nome_arquivo):
    quantidade_vetores = int(input("Quantidade de Vetores desordenados: "))
    with open(nome_arquivo, "w") as arquivo:
        arquivo.write(f"{quantidade_vetores}")
        for _ in range(quantidade_vetores):
            tamanho_vetor = random.randint(5, 20)
            vetor1 = " ".join(str(random.randint(-997402, 1562 )) for _ in range(int(tamanho_vetor/2)))
            vetor2 = " ".join(str(random.randint(1, 100 )) for _ in range(int(tamanho_vetor/2)))
            arquivo.write(f"{tamanho_vetor}\n{vetor1} {vetor2}\n")

    print(f"O arquivo {nome_arquivo} foi criado com sucesso!")


nome_arquivo = input("Digite o nome do arquivo a ser criado: ")
criar_arquivo_vetores_desordenados(nome_arquivo)
