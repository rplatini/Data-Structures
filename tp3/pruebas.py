from grafo import Grafo
from pila import Pila

ERROR_LECTURA = "No existe forma de leer las paginas en orden"

def imprimir_salida(resultado): 
    print(', '.join(resultado))

def _dfs(grafo, v, visitados, pila, paginas):
    visitados.add(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            _dfs(grafo, w, visitados, pila, paginas)
    if v in paginas:
        pila.apilar(v)


def topologico_dfs(grafo, paginas):
    visitados = set()
    pila = Pila()

    for v in grafo.obtener_vertices():
        if v not in visitados:
            _dfs(grafo, v, visitados, pila, paginas)

    orden = pila_a_lista(pila)
    if len(orden) != len(paginas): return None
    return orden


def pila_a_lista(pila):
    lista = []
    while not pila.esta_vacia():
        lista.append(pila.desapilar())
    return lista


def main():
    vertices = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K']
    grafo = Grafo(True, False, vertices)

    grafo.agregar_arista('A', 'B')
    grafo.agregar_arista('A', 'D')
    grafo.agregar_arista('A', 'I')
    grafo.agregar_arista('B', 'H')
    grafo.agregar_arista('B', 'K')
    grafo.agregar_arista('C', 'J')
    grafo.agregar_arista('C', 'H')
    grafo.agregar_arista('D', 'E')
    grafo.agregar_arista('F', 'B')
    grafo.agregar_arista('F', 'C')
    grafo.agregar_arista('G', 'J')
    grafo.agregar_arista('H', 'G')
    grafo.agregar_arista('I', 'A')
    grafo.agregar_arista('J', 'D')
    grafo.agregar_arista('K', 'E')

    paginas = ['A', 'I']
    orden = topologico_dfs(grafo, paginas)

    if orden == None:
        print(ERROR_LECTURA)
    else: imprimir_salida(orden)

main()