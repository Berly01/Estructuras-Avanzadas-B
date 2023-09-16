import matplotlib.pyplot as plt

#Lee los archivos creados por 'Lab1.cpp' y retorna una lista de datos float'
def read_file(file_path: str):
    results = []
    with open(file_path, 'r') as file:
        for num in file:
            results.append(float(num)) 
    return results

#Grafica y exporta el grafico de resultados
if __name__ == "__main__":
      
    DIMENSIONS = [2, 10, 50, 100, 500, 1000, 2000, 5000]
    FILE_PATH = "results_dimension_"
    b = 5 #Numero de barras
    for i in DIMENSIONS :
        file = f"{FILE_PATH}{i}.txt"
        results = read_file(file)
        b += 12
        plt.hist(results, range=(0.0, max(results)), bins=b, edgecolor='black')  
        plt.title("Histograma de las distancias entre puntos con dimension " + str(i))
        plt.xlabel("Distancia")
        plt.ylabel("Frecuencia")
        plt.savefig(f"{FILE_PATH}{i}.jpeg")
        plt.close()


