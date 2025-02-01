#============================================================ INTEGRANTES ================================================================
#ALUNO: DIOGO AUGUSTO SILVERIO NASCIMENTO RA: a2586460
#ALUNO: MATHEUS OTENIO RA: a2553139
#=======================================================================================================================================

# -----------------------------------------------------------------------------------
# Função: Escrita de registros com índice no formato com prefixo de índice
# Params:
#         - registrosAnimes: lista com os registros de animes lidos na memória
#         - arquivoSaida: arquivo de saída com os registros formatados
# -----------------------------------------------------------------------------------
def EscritaRegistrosComIndice(registrosAnimes, arquivoSaida="animes.txt"):
    with open(arquivoSaida, mode="w", encoding="utf-8") as file:
        # Cabeçalho inicial: -1 indica que não há registros removidos
        file.write("-1\n")
        
        for indice, registro in enumerate(registrosAnimes):
            # Substituir vírgulas por pipe (|) e criar prefixo
            novoRegistro = registro.replace(",", "|").strip()
            novoRegistro = f"{indice:03d}{novoRegistro}"  # Prefixo com índice do anime (3 dígitos)
            file.write(novoRegistro + "\n")

# -----------------------------------------------------------------------------------
# Função: Leitura de registros com índice
# Params:
#         - arquivoEntrada: arquivo de onde os registros serão lidos
# -----------------------------------------------------------------------------------
def LeituraRegistrosComIndice(arquivoEntrada="animes.txt"):
    with open(arquivoEntrada, mode="r", encoding="utf-8") as file:
        registros = file.readlines()
        return registros

# -----------------------------------------------------------------------------------
# Função: Inserir registro com reuso
# Parâmetros:
#         - arquivo: arquivo de entrada/saída onde o registro será inserido
#         - registro: registro que será inserido
# -----------------------------------------------------------------------------------
def inserirRegistroComReuso(arquivo, registro):
    with open(arquivo, mode="r+", encoding="utf-8") as file:
        # Ler o cabeçalho para obter a lista de espaços livres
        file.seek(0)
        cabecalho = file.readline().strip()
        espacoLivre = int(cabecalho)

        # Substituir vírgulas por pipe (|) e criar prefixo
        novoRegistro = registro.replace(",", "|").strip()

        # Gerar o índice do novo registro
        file.seek(0)
        linhas = file.readlines()
        ultimoIndice = int(linhas[-1][:3]) if len(linhas) > 1 else -1
        novoIndice = ultimoIndice + 1 if espacoLivre == -1 else espacoLivre
        novoRegistro = f"{novoIndice:03d}{novoRegistro}"  # Adicionar índice como prefixo
        
        if espacoLivre == -1:  # Sem espaços livres, adicionar ao final
            file.seek(0, 2)  # Ir para o final do arquivo
            file.write(novoRegistro + "\n")
        else:  # Reutilizar espaço livre
            RRN = espacoLivre
            linhas[espacoLivre + 1] = novoRegistro + "\n"  # +1 por causa do cabeçalho

            # Atualizar o cabeçalho com o próximo espaço livre
            proxEspacoLivre = int(linhas[espacoLivre + 1][:3]) if len(linhas) > espacoLivre + 1 else -1
            linhas[0] = f"{proxEspacoLivre}\n"

            # Reescrever o arquivo
            file.seek(0)
            file.writelines(linhas)
        
        return novoIndice

# -----------------------------------------------------------------------------------
# Função: Remover registro
# Parâmetros:
#         - arquivo: arquivo de entrada/saída onde o registro será removido
#         - indice: índice do registro a ser removido
# -----------------------------------------------------------------------------------
def removerRegistro(arquivo, indice):
    with open(arquivo, mode="r+", encoding="utf-8") as file:
        # Ler o cabeçalho para obter o índice do espaço livre atual
        file.seek(0)
        cabecalho = file.readline().strip()
        espacoLivre = int(cabecalho)

        # Ler todos os registros
        linhas = file.readlines()
        
        # Verificar se o índice é válido
        if indice < 0 or indice >= len(linhas):
            print(f"Erro: índice {indice} inválido para remoção.")
            return False, None  # Retorna False e None em caso de erro

        # Marcar o registro como removido
        registroRemovido = linhas[indice + 1]  # +1 porque a linha 0 é o cabeçalho
        linhas[indice + 1] = f"{espacoLivre:03d}REMOVIDO\n"

        # Atualizar o cabeçalho com o índice do registro removido
        linhas[0] = f"{indice}\n"

        # Reescrever o arquivo
        file.seek(0)
        file.writelines(linhas)

        print(f"Registro removido no índice {indice}: {registroRemovido.strip()}")

        return True, registroRemovido  # Retorna sucesso e o registro removido

# -----------------------------------------------------------------------------------
# Função principal (main)
# -----------------------------------------------------------------------------------
if __name__ == "__main__":
    # Leitura do arquivo original
    with open("animes.csv", mode="r", encoding="utf-8") as f:
        registrosAnimes = f.readlines()

    # Remover o cabeçalho
    registrosAnimes.pop(0)

    # Escrita no formato com índices
    EscritaRegistrosComIndice(registrosAnimes, "animes.txt")

    # Remoção de um registro
    indiceParaRemover = 2
    sucesso, registroRemovido = removerRegistro("animes.txt", indiceParaRemover)  # Remove o registro de índice 2

    # Inserção com reuso
    novoRegistro = "Bleach,Action,2024"
    inserirRegistroComReuso("animes.txt", novoRegistro)

    # Validação
    registrosLidos = LeituraRegistrosComIndice("animes.txt")
    print("Registros lidos após remoção e inserção:")
    for registro in registrosLidos:
        print(registro.strip())

    if sucesso:  # Se a remoção foi bem-sucedida, exibe o registro removido
        print("\n\n==============================================================================\n")
        print(f"Registro removido no índice {indiceParaRemover}: {registroRemovido.strip()}")
        print("\n==============================================================================\n\n")
