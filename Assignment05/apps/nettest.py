import networkx as nx
from math import log, e

edges = [(0, 7, {'weight': 0.16}),
         (0, 2, {'weight':0.26}),
         (0, 4, {'weight':0.38}),
         (6, 0, {'weight':0.58}),
         (1, 7, {'weight':0.19}),
         (5, 7, {'weight':0.28}),
         (2, 7, {'weight':0.34}),
         (4, 7, {'weight':0.37}),
         (1, 3, {'weight':0.29}),
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

print(list(G.neighbors(0)))
