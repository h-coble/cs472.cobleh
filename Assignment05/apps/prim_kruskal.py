import networkx as nx
from math import inf
from queue import PriorityQueue

def my_prim(G: nx.Graph, s, weight):
    color = []
    d = {}
    for node in G.nodes():
        color.insert(node, "white")
        d[node] = inf

    color[s] = "gray"
    d[s] = 0

    pq = PriorityQueue()
    weight = nx.get_edge_attributes(G,'weight')

    out = None
    pq.put((0, s))

    p = {s: s}
    while not pq.empty():
        u = pq.get()
        nl = list(G.neighbors(u[1]))
        for neighbor in nl:
            try:
                if weight[(u[1],neighbor)] < d[neighbor]:
                    d[neighbor] = weight[(u[1],neighbor)]
                    p[neighbor] = u
                    if color[neighbor] == "white":
                        pq.put((weight[(u[1],neighbor)], neighbor))
                        color[neighbor]=="gray"
                    elif color[neighbor] == "gray":                     
                        pq.put((weight[(u[1],neighbor)], neighbor))
            except KeyError:
                if weight[(neighbor, u[1])] < d[u[1]]:
                    d[neighbor] = weight[(neighbor, u[1])]
                    p[neighbor] = u
                    if color[neighbor] == "white":
                        pq.put((weight[(neighbor, u[1])], neighbor))
                        color[neighbor]=="gray"
                    elif color[neighbor] == "gray":                     
                        pq.put((weight[(neighbor, u[1])], neighbor))
        color[u[1]] = "black"
    return (p,d)
#Gets incorrect weights and creates paradoxical pred records

edges = [(0, 7, {'weight': 0.16}),
         (0, 2, {'weight':0.26}),
         (0, 4, {'weight':0.38}),
         (6, 0, {'weight':0.58}),
         (1, 7, {'weight':0.19}),
         (5, 7, {'weight':0.28}),
         (2, 7, {'weight':0.34}),
         (4, 7, {'weight':0.37}),
         (1, 3, {'weight':0.29}),

        #Shouldn't be in MinST
         (1, 5, {'weight':0.32}),
         
         (1, 2, {'weight':0.36}),
         (2, 3, {'weight':0.17}),
         (6, 2, {'weight':0.40}),
         (3, 6, {'weight':0.52}),
         (4, 5, {'weight':0.35}),
         (6, 4, {'weight':0.93})
         ]

G = nx.Graph()
for n in [0,1,2,3,4,5,6,7]:
    G.add_node(n)
G.add_edges_from(edges)
print(G)

mst = my_prim(G, 0,'weight')

print(mst[0])
print(mst[1])

T = nx.minimum_spanning_tree(G,'weight','prim')
for edge in T.edges:
    print(str(edge) + "\t" + str(nx.get_edge_attributes(G,'weight')[edge]))
