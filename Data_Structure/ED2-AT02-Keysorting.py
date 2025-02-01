#============================================================ INTEGRANTES ================================================================
#ALUNO: DIOGO AUGUSTO SILVERIO NASCIMENTO RA: a2586460
#ALUNO: MATHEUS OTENIO RA: a2553139
#=======================================================================================================================================

import sys

# Estrutura para armazenar os registros
class Heroi:
    def __init__(self, campos):
        self.key = int(campos[0])  
        self.name = campos[1]      
        self.alignment = campos[2] 
        self.gender = campos[3]   
        self.eye_color = campos[4] 
        self.race = campos[5]     
        self.hair_color = campos[6] 
        self.publisher = campos[7] 
        self.skin_color = campos[8] 
        self.height = float(campos[9]) if campos[9] != '-99' else -1 
        self.weight = float(campos[10]) if campos[10] != '-99' else -1 
        self.intelligence = int(campos[11])
        self.strength = int(campos[12])
        self.speed = int(campos[13])
        self.durability = int(campos[14])
        self.power = int(campos[15])
        self.combat = int(campos[16])
        self.total = int(campos[17])
      
    def __repr__(self):
        return f"{self.key}|{self.name}|{self.alignment}|{self.gender}|{self.eye_color}|{self.race}|{self.hair_color}|{self.publisher}|{self.skin_color}|{self.height}|{self.weight}|{self.intelligence}|{self.strength}|{self.speed}|{self.durability}|{self.power}|{self.combat}|{self.total}"


# Função para ler e interpretar o arquivo
def ler_arquivo():
    try:
        # Alterado para sempre usar 'entrada1.txt' como arquivo de entrada
        with open('entrada1.txt', 'r', encoding='utf-8') as arquivo:
            # Ler o cabeçalho
            cabecalho = arquivo.readline().strip()  # SORT e ORDER
            sort, order = cabecalho.split(',')[0].split('=')[1], cabecalho.split(',')[1].split('=')[1]

            # Verificar se os valores de 'sort' e 'order' são válidos
            if sort not in ['Q', 'H', 'M', 'I'] or order not in ['C', 'D']:
                return "Entrada Inválida!", None, None
            
            # Ignorar a linha com os nomes dos campos
            arquivo.readline()

            # Ler os registros
            registros = []
            for linha in arquivo:
                linha = linha.strip()
                if linha:
                    campos = linha.split('|')
                    heroi = Heroi(campos)
                    registros.append(heroi)

            return sort, order, registros
    except FileNotFoundError:
        print(f"Erro: Arquivo 'entrada1.txt' não encontrado.")
        return None, None, []
    except Exception as e:
        print(f"Erro: {e}")
        return None, None, []


# Função para ordenar registros
def ordenar_registros(registros, metodo, ordem):
    if metodo == 'Q':  # Quick Sort
        quick_sort(registros, 0, len(registros) - 1)
    elif metodo == 'H':  # Heap Sort
        heap_sort(registros)
    elif metodo == 'M':  # Merge Sort
        registros[:] = merge_sort(registros)
    elif metodo == 'I':  # Insertion Sort
        insertion_sort(registros)
    
    # Inverter a ordem, se necessário
    if ordem == 'D':  # Ordem decrescente
        registros.reverse()
    return registros


# Algoritmo Quick Sort
def quick_sort(lista, inicio, fim):
    if inicio < fim:
        pivo = particionar(lista, inicio, fim)
        quick_sort(lista, inicio, pivo - 1)
        quick_sort(lista, pivo + 1, fim)


# Função auxiliar para particionar a lista no Quick Sort
def particionar(lista, inicio, fim):
    pivo = lista[fim].key
    i = inicio - 1
    for j in range(inicio, fim):
        if lista[j].key <= pivo:  # Comparação com a chave
            i += 1
            lista[i], lista[j] = lista[j], lista[i]  # Troca de posições
    lista[i + 1], lista[fim] = lista[fim], lista[i + 1]
    return i + 1


# Algoritmo Heap Sort
def heap_sort(lista):
    n = len(lista)

    # Construir o heap máximo
    for i in range(n // 2 - 1, -1, -1):
        heapify(lista, n, i)

    # Extrair elementos do heap um a um
    for i in range(n - 1, 0, -1):
        lista[i], lista[0] = lista[0], lista[i]  # Trocar o primeiro elemento com o último
        heapify(lista, i, 0)  

# Função auxiliar para manter a propriedade do heap
def heapify(lista, n, i):
    maior = i
    esquerda = 2 * i + 1
    direita = 2 * i + 2

    # Verificar se o filho esquerdo é maior que o pai
    if esquerda < n and lista[esquerda].key > lista[maior].key:
        maior = esquerda

    # Verificar se o filho direito é maior que o maior
    if direita < n and lista[direita].key > lista[maior].key:
        maior = direita

    # Se o maior não for o nó atual, trocar e continuar a organização
    if maior != i:
        lista[i], lista[maior] = lista[maior], lista[i]
        heapify(lista, n, maior)


# Algoritmo Merge Sort
def merge_sort(lista):
    if len(lista) > 1:
        meio = len(lista) // 2  
        esquerda = lista[:meio]  
        direita = lista[meio:]

        # Chamar merge_sort recursivamente nas duas metades
        merge_sort(esquerda)
        merge_sort(direita)

        i = j = k = 0

        # Combinar as duas metades
        while i < len(esquerda) and j < len(direita):
            if esquerda[i].key < direita[j].key:
                lista[k] = esquerda[i]
                i += 1
            else:
                lista[k] = direita[j]
                j += 1
            k += 1

        # Verificar se há elementos restantes na metade esquerda
        while i < len(esquerda):
            lista[k] = esquerda[i]
            i += 1
            k += 1

        # Verificar se há elementos restantes na metade direita
        while j < len(direita):
            lista[k] = direita[j]
            j += 1
            k += 1

    return lista


# Algoritmo Insertion Sort
def insertion_sort(lista):
    for i in range(1, len(lista)):
        chave = lista[i]
        j = i - 1
        while j >= 0 and lista[j].key > chave.key:
            lista[j + 1] = lista[j]
            j -= 1
        lista[j + 1] = chave


# Função principal para rodar o programa com parâmetros de linha de comando
def main():
    if len(sys.argv) != 3:
        print("Uso incorreto. A sintaxe correta é: python keysorting.py [arquivo de entrada] [arquivo de saída]")
        sys.exit(1)

    arquivo_entrada = sys.argv[1]
    arquivo_saida = sys.argv[2]

    sort, order, registros = ler_arquivo()

    with open(arquivo_saida, 'w', encoding='utf-8') as saida:
        if sort == "Entrada Inválida!":
            saida.write("Arquivo Inválida!\n")
        else:
            # Ordenar os registros com Quick Sort, Heap Sort, Merge Sort ou Insertion Sort
            registros_ordenados = ordenar_registros(registros, sort, order)

            # Escrever cabeçalho no arquivo de saída
            saida.write(f"SORT={sort},ORDER={order}\n")
            saida.write("key|name|alignment|gender|eye_color|race|hair_color|publisher|skin_color|height|weight|intelligence|strength|speed|durability|power|combat|total\n")
            for registro in registros_ordenados:
                saida.write(f"{registro}\n")


# Chama a função principal ao rodar o programa
if __name__ == "__main__":
    main() 
