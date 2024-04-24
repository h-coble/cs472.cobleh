def backtrack(coins, pairs, moves):
    if len(pairs) == len(coins) // 2:
        return moves
    min_moves = float('inf')
    for i in range(len(coins) - 2):
        if i not in pairs and i + 1 not in pairs and i + 2 not in pairs:
            new_pairs = pairs + [i]
            min_moves = min(min_moves, backtrack(coins, new_pairs, moves + 1))
    return min_moves

def solve_puzzle(n):
    if n % 2 != 0:
        return "No solution exists for odd n"
    coins = [i for i in range(n)]
    return backtrack(coins, [], 0)

# Test the algorithm
even_n = 4  # Example even value of n
print(f"Minimum number of moves for n={even_n}: {solve_puzzle(even_n)}")