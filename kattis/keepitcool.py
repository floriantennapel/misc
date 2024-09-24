s = 3
d = 4

memo = dict()
def score(cold, warm, left):
    if left == 0:
        return 0
    
    if (cold, warm, left) in memo:
        return memo[(cold, warm, left)]
    

    
