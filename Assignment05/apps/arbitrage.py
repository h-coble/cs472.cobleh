#Walkthrough of the concept found at 
#https://hackernoon.com/arbitrage-as-a-shortest-path-problem-u2l34ow

#Log for edge weights/exhange rates
#This changes sum to product
from math import log, e
import networkx as nx

#Felt easier to do this instead of typing "{'weight': log(x, 10)}" for every edge,
#...smarter not harder I guess?
def weight_alias(x: float):
    return {'weight': -log(x)}

edges = [("USD", "GBP", weight_alias(0.75)),
         ("GBP", "AUD", weight_alias(2)),
         ("AUD", "USD", weight_alias(0.7))]


def main():
    #Set up Graph
    G = nx.DiGraph()
    for currency in ["USD", "GBP", "AUD"]:
        G.add_node(currency)
    G.add_edges_from(edges)
    G.to_undirected()
    #Profitable exchange will always be a negative cycle
    #Networkx's all_pairs_bellman_ford_path excepts when a negative cycle is found;
    #Documentation says to use find_negative_cycle to analyze the path, which uses another implementation of bellman_ford
    #https://networkx.org/documentation/stable/_modules/networkx/algorithms/shortest_paths/weighted.html#all_pairs_bellman_ford_path
    #This is the path we want.
    try:
        path = nx.find_negative_cycle(G,"USD")
    except nx.exception.NetworkXError:
        print("There is no profitable exchange path for USD.")
        return
    
    print("\nPath: " + str(path[1:]))
    #Path weight = sum of edge weights
    #ln(a) + ln (b) = ln(ab)
    profit = nx.path_weight(G, path, 'weight')

    #cancel ln -> resultant amount
    profit = pow(e,-profit)

    #Round to 2 decimal places because USD
    profit = round(profit, 2)
    print("$" + str(profit))
    return

main()