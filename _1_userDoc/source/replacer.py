import os

print ("liste rst file")

liste=os.listdir()

    
liste = [ a for a in liste if a.find(".rst") != -1]
# liste = [a for a in liste if a == "mockup.rst"]
print(liste)

listeFichierApb = [] 
listeLigneApb = []


for file in liste:
    f = open(file, "r")
    cptTitre1 = 0
    cptLigneEgal = 0
    cptLigne = 0
    listeLigneApb = []
    print("Traitement de : " +file)
    line = f.readline()
    cptLigne += 1
    while line:
        if line.startswith('==='):
            # print(line)
            cptLigneEgal += 1
            f.readline() #skip title
            cptLigne += 1
            line = f.readline()
            cptLigne += 1
            # print(line)
            if line.startswith('==='):
                cptLigneEgal += 1
                cptTitre1 += 1
            else:
                listeLigneApb.append(cptLigne-2)
        line = f.readline()
        cptLigne += 1
    if (cptLigneEgal/2 != cptTitre1):
        listeFichierApb.append(file)
        print("\tnbr ligne === trouvées {}".format(cptLigneEgal) )
        print("\tnbr de ligne de titre 1 trouvée : {}".format(cptTitre1) )
        print("liste des lignes en erreur:")
        print(listeLigneApb)
        print()
    f.close()
 


print("fichiers a bp:")
print(listeFichierApb)