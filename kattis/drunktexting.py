def drunkify(s1, s2):
    i = j = 0
    s = ['']

    while i < len(s1) and j < len(s2):
        ic, jc = s1[i], s2[j]

        if ic == jc:
            s.append(ic)
            i += 1
            j += 1
            continue
        
        ind_ic = s2[j:].find(ic)
        ind_jc = s1[i:].find(jc)

        if ind_ic == -1 or (ind_jc != -1 and ind_ic > ind_jc):
            s.append(ic)
            i += 1
        else:
            s.append(jc)
            j += 1
    
    if i < len(s1):
        s += s1[i:]
    elif j < len(s2):
        s += s2[j:]
    
    return ''.join(s)

print(drunkify(input().strip(), input().strip()))
