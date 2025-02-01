#============================================================ INTEGRANTES ================================================================
#ALUNO: DIOGO AUGUSTO SILVERIO NASCIMENTO RA: a2586460
#ALUNO: MATHEUS OTENIO RA: a2553139
#=======================================================================================================================================

import random
import time
import sys
sys.setrecursionlimit(2000)  # Ajuste o limite conforme necessário

#================================================================= SELECTIONSORT ===================================================================

def selectionSort(V, tam):
    comparacoes = 0  # Contador de comparações
    for N in range(0, tam):
        menor = V[N]   # Chutando que o V[N] é o menor elemento
        indice = N     # Inicializa o índice do menor valor
        
        for i in range(N, tam):  # Percorre o subvetor ainda desordenado
            comparacoes += 1
            if V[i] < menor:     # Encontra o menor valor no subvetor
                menor = V[i]
                indice = i
        
        # Troca os elementos se necessário
        if menor != V[N]:
            aux = V[N]
            V[N] = V[indice]
            V[indice] = aux
    
    return V, comparacoes

#================================================================= HEAPSORT ===================================================================

def heapify(V, n, i):
    comparacoes = 0
    maior = i  # Inicializa o maior como raiz
    esquerda = 2 * i + 1  # Esquerda = 2*i + 1
    direita = 2 * i + 2  # Direita = 2*i + 2

    # Verifica se a esquerda existe e é maior que a raiz
    if esquerda < n and V[esquerda] > V[maior]:
        maior = esquerda
        comparacoes += 1

    # Verifica se a direita existe e é maior que a raiz
    if direita < n and V[direita] > V[maior]:
        maior = direita
        comparacoes += 1

    # Se o maior não for a raiz, faz a troca
    if maior != i:
        V[i], V[maior] = V[maior], V[i]
        comparacoes += heapify(V, n, maior)  # Recursão para heapificar o sub-árvore

    return comparacoes

def heapSort(V):
    n = len(V)
    comparacoes = 0

    # Constroi o heap (rearranja o vetor)
    for i in range(n // 2 - 1, -1, -1):
        comparacoes += heapify(V, n, i)

    # Extrai os elementos do heap um por um
    for i in range(n - 1, 0, -1):
        V[i], V[0] = V[0], V[i]  # Troca
        comparacoes += heapify(V, i, 0)  # Reajusta o heap

    return V, comparacoes

#================================================================= COCKTAIL SORT ===================================================================

def cocktail_sort(lista):
    n = len(lista)
    trocou = True
    inicio = 0
    fim = n - 1
    comparacoes = 0

    while trocou:
        trocou = False

        # Passagem da esquerda para a direita
        for i in range(inicio, fim):
            comparacoes += 1
            if lista[i] > lista[i + 1]:
                lista[i], lista[i + 1] = lista[i + 1], lista[i]
                trocou = True

        if not trocou:
            break

        fim -= 1
        trocou = False

        # Passagem da direita para a esquerda
        for i in range(fim, inicio, -1):
            comparacoes += 1
            if lista[i] < lista[i - 1]:
                lista[i], lista[i - 1] = lista[i - 1], lista[i]
                trocou = True

        inicio += 1

    return lista, comparacoes

#================================================================= QUICKSORT ===================================================================

def quicksort(v, inicio, fim, comparacoes):
    if inicio < fim:
        pivo, comparacoes = particiona(v, inicio, fim, comparacoes)
        comparacoes = quicksort(v, inicio, pivo - 1, comparacoes)
        comparacoes = quicksort(v, pivo + 1, fim, comparacoes)
    return comparacoes

def particiona(v, inicio, fim, comparacoes):
    # Escolhe um pivô aleatório entre 'inicio' e 'fim'
    pivo_index = random.randint(inicio, fim)
    v[inicio], v[pivo_index] = v[pivo_index], v[inicio]  # Troca o pivô com o primeiro elemento
    esq = inicio + 1
    dir = fim
    pivo = v[inicio]
    
    while esq <= dir:
        while esq <= fim and v[esq] <= pivo:
            esq += 1
            comparacoes += 1
        while v[dir] > pivo:
            dir -= 1
            comparacoes += 1
        
        if esq < dir:
            v[esq], v[dir] = v[dir], v[esq]
            comparacoes += 1
    
    v[dir], v[inicio] = v[inicio], v[dir]
    comparacoes += 1
    return dir, comparacoes

# Função para gerar um vetor conforme o modo especificado
def gerar_vetor(tamanho, modo):
    if modo == 'c':  # Crescente
        return list(range(1, tamanho + 1))
    elif modo == 'd':  # Decrescente (gerado crescente e depois ordenado)
        return list(range(1, tamanho + 1))  # Gerado crescente
    elif modo == 'r':  # Aleatório
        return [random.randint(0, 32000) for _ in range(tamanho)]
    else:
        raise ValueError("Modo invalido. Use 'c', 'd' ou 'r'.")
    
#=================================================================================================================================#


# Função para gravar resultados em arquivo
def gravar_resultados(arquivo_saida, metodo, vetor, comparacoes, tempo_gasto):
    with open(arquivo_saida, 'a') as f_saida:  # Modo 'a' para adicionar
        f_saida.write(f'Metodo de ordenacao: {metodo}\n')
        f_saida.write('Array ordenado: ' + ' '.join(map(str, vetor)) + '\n')
        f_saida.write(f'Numero de comparacoes: {comparacoes}\n')
        f_saida.write(f'Tempo gasto: {tempo_gasto:.4f} ms\n')
        f_saida.write('\n')

#========================================= MATHEUS

# Funcao Insertion Sort
def insertion_sort(vetor):
    comparacoes = 0
    inicio_tempo = time.time()
    
    for i in range(1, len(vetor)):
        aux = vetor[i]
        j = i - 1
        while j >= 0:
            comparacoes += 1
            if aux < vetor[j]:
                vetor[j + 1] = vetor[j]
                j -= 1
            else:
                break
        vetor[j + 1] = aux
    
    fim_tempo = time.time()
    tempo_gasto = (fim_tempo - inicio_tempo) * 1000
    return vetor, comparacoes, tempo_gasto

# Funcao Bubble Sort
def bubble_sort(vetor):
    comparacoes = 0
    inicio_tempo = time.time()
    n = len(vetor)
    
    for i in range(n):
        for j in range(0, n - i - 1):
            comparacoes += 1
            if vetor[j] > vetor[j + 1]:
                vetor[j], vetor[j + 1] = vetor[j + 1], vetor[j]
    
    fim_tempo = time.time()
    tempo_gasto = (fim_tempo - inicio_tempo) * 1000
    return vetor, comparacoes, tempo_gasto

# Funcao Merge Sort com contagem de comparacoes
def mergeSort(V, inicio, fim, contador_comparacoes):
    if inicio < fim:
        meio = (inicio + fim) // 2
        contador_comparacoes = mergeSort(V, inicio, meio, contador_comparacoes)
        contador_comparacoes = mergeSort(V, meio + 1, fim, contador_comparacoes)
        contador_comparacoes = merge(V, inicio, meio, fim, contador_comparacoes)
    return contador_comparacoes

def merge(V, inicio, meio, fim, contador_comparacoes):
    aux = []
    p1 = inicio
    p2 = meio + 1

    while p1 <= meio and p2 <= fim:
        contador_comparacoes += 1
        if V[p1] <= V[p2]:
            aux.append(V[p1])
            p1 += 1
        else:
            aux.append(V[p2])
            p2 += 1

    while p1 <= meio:
        aux.append(V[p1])
        p1 += 1

    while p2 <= fim:
        aux.append(V[p2])
        p2 += 1

    for i in range(len(aux)):
        V[inicio + i] = aux[i]

    return contador_comparacoes

#=============================================

# Função principal
def main(arquivo_entrada, arquivo_saida):
    # Abrindo o arquivo de entrada
    with open(arquivo_entrada, 'r') as f:
        tamanho = int(f.readline().strip())  # Tamanho do vetor
        modo = f.readline().strip()  # Modo de geração
 
    # Gerando o vetor conforme o modo de geração
    vetor = gerar_vetor(tamanho, modo)

    with open(arquivo_saida, 'w') as f_saida:  # Modo 'a' para adicionar
        f_saida.write(f'RESULTADO: \n')

    # ==================== INSERTION SORT ====================
    vetor_insertion = vetor[:]
    vetor_insertion, comparacoes, tempo_gasto = insertion_sort(vetor_insertion)
    gravar_resultados(arquivo_saida, "Insertion Sort", vetor_insertion, comparacoes, tempo_gasto)

    # ==================== SELECTION SORT ====================
    vetor_selecionado = vetor[:]
    inicio_tempo = time.time()
    vetor_selecionado, comparacoes = selectionSort(vetor_selecionado, len(vetor_selecionado))
    tempo_gasto = (time.time() - inicio_tempo) * 1000
    gravar_resultados(arquivo_saida, "Selection Sort", vetor_selecionado, comparacoes, tempo_gasto)

    # ==================== BUBBLE SORT ====================
    vetor_bubble = vetor[:]
    vetor_bubble, comparacoes, tempo_gasto = bubble_sort(vetor_bubble)
    gravar_resultados(arquivo_saida, "Bubble Sort", vetor_bubble, comparacoes, tempo_gasto)

    # ==================== MERGE SORT ====================
    vetor_merge = vetor[:]
    inicio_tempo = time.time()
    comparacoes = 0
    comparacoes = mergeSort(vetor_merge, 0, len(vetor_merge) - 1, comparacoes)
    tempo_gasto = (time.time() - inicio_tempo) * 1000
    gravar_resultados(arquivo_saida, "Merge Sort", vetor_merge, comparacoes, tempo_gasto)

    # ==================== QUICK SORT ====================
    vetor_quick = vetor[:]
    inicio_tempo = time.time()
    comparacoes = 0
    comparacoes = quicksort(vetor_quick, 0, len(vetor_quick) - 1, comparacoes)
    tempo_gasto = (time.time() - inicio_tempo) * 1000
    gravar_resultados(arquivo_saida, "Quick Sort", vetor_quick, comparacoes, tempo_gasto)

    # ==================== HEAP SORT ====================
    vetor_heap = vetor[:]
    inicio_tempo = time.time()
    vetor_heap, comparacoes = heapSort(vetor_heap)
    tempo_gasto = (time.time() - inicio_tempo) * 1000
    gravar_resultados(arquivo_saida, "Heap Sort", vetor_heap, comparacoes, tempo_gasto)

    # ==================== COCKTAIL SORT ====================
    vetor_cocktail = vetor[:]
    inicio_tempo = time.time()
    vetor_cocktail, comparacoes = cocktail_sort(vetor_cocktail)
    tempo_gasto = (time.time() - inicio_tempo) * 1000
    gravar_resultados(arquivo_saida, "Cocktail Sort", vetor_cocktail, comparacoes, tempo_gasto)

# Exemplo de uso
if __name__ == "__main__":
    arquivo_entrada = "entrada.txt"
    arquivo_saida = "saida.txt"
    main(arquivo_entrada, arquivo_saida)
    heap_sort(array)
    shellsort(array, arquivo_saida)
    quick_sort(array, arquivo_saida)
