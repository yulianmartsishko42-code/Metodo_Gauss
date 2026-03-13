#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Gauss
{
private:
    vector<vector<int>> matriz_;
    vector<int> terminos_independientes_;
    vector<vector<int>> matriz_gaussiana_;
    int orden_matriz_;

public:
    Gauss(int n) : orden_matriz_(n)
    {
        matriz_.resize(orden_matriz_);
        for (int i = 0; i < orden_matriz_; i++)
        {
            matriz_[i].resize(orden_matriz_);
        }
        terminos_independientes_.resize(orden_matriz_);
        matriz_gaussiana_.resize(orden_matriz_);
        for (int i = 0; i < orden_matriz_; i++)
        {
            matriz_gaussiana_[i].resize(orden_matriz_ + 1);
        }
    }
    void solicitar_valores(void)
    {
        for (int i = 0; i < orden_matriz_; i++) ///incognitas ecuaciones
        {
            int valor = 0;
            cout << endl << "VALORES COEFICIENTES ECUACION " << i + 1;
            for (int j = 0; j < orden_matriz_; j++)
            {
                cout << endl << "Introduzca valor de la incognita " << j + 1 << ": ";
                cin >> valor;
                matriz_[i][j] = valor;
            }
        }
        cout << endl << "TERMINOS INDEPENDIENTES";
        for (int i = 0; i < orden_matriz_; i++) ///terminos independientes
        {
            int valor = 0;
            cout << endl << "Introduzca valor termino independiente " << i + 1 << ": ";
            cin >> valor;
            terminos_independientes_[i] = valor;
        }
    }
    void unir_matriz_con_terminos_independientes(void)
    {
        for (int i = 0; i < matriz_gaussiana_.size(); i++)
        {
            for (int j = 0; j < matriz_gaussiana_[i].size(); j++)
            {
                if (j < matriz_gaussiana_[i].size() - 1)
                {
                    matriz_gaussiana_[i][j] = matriz_[i][j];
                }
                else if (j == matriz_gaussiana_[i].size() - 1)
                {
                    matriz_gaussiana_[i][j] = terminos_independientes_[i];
                }
            }
        }
    }
    bool matriz_escalonada(void) const
    {
        for (int i = 1; i < matriz_gaussiana_.size(); i++)
        {
            int n_ceros_en_fila = 0;
            for (int j = 0; j < matriz_gaussiana_[i].size(); j++)
            {
                if (matriz_gaussiana_[i][j] == 0) n_ceros_en_fila++;
                else if (matriz_gaussiana_[i][j] != 0) break;
            }
            if (n_ceros_en_fila >= i) continue;
            else return false;
        }
        return true;
    }
    int calcular_fila_referencia(int fila_) const
    {
        int fila_referrencia = 0;
        int n_ceros = 0;
        for (int columna = 0; columna < matriz_gaussiana_[fila_].size(); columna++)
        {
            //para la fila dada, calculo cuantos ceros tiene la fila. Si me encuentro un numero que no es 0, paro el bucle.
            if (matriz_gaussiana_[fila_][columna] == 0) n_ceros++;
            else if (matriz_gaussiana_[fila_][columna] != 0) break;
        }
        if (n_ceros != 0)
        {
            fila_referrencia = fila_ - n_ceros;
        }
        return fila_referrencia;
    }
    bool fila_no_ok(int fila_) const
    {
        int n_ceros = 0;
        //cuento los ceros que hay en la fila "fila".
        for (int columna = 0; columna < matriz_gaussiana_[fila_].size(); columna++)
        {
            if (matriz_gaussiana_[fila_][columna] == 0) n_ceros++;
            else if (matriz_gaussiana_[fila_][columna] != 0) break;
        }
        //si el numero de ceros en la fila "fila" es igual o mayor que el valor de la fila, devolvemos false, ya que la fila esta OK 
        if (n_ceros >= fila_) return false;
        else return true;
    }
    void pintar_matriz(void) const
    {
        cout << endl << endl;
        for (const auto& i : matriz_gaussiana_)
        {
            cout << setw(5);
            for (const auto& j : i)
            {
                cout << j << setw(5);
            }
            cout << endl;
        }
    }
    void escalonar_matriz_gaussiana()
    {
        //mientras la matriz no este escalonada, ejecutamos los bucles hasta escalonarla
        while (not(matriz_escalonada()))
        {
            for (int i = 1; i < matriz_gaussiana_.size(); i++)
            {
                int factor1 = 0, factor2 = 0;
                //si la fila "i" no esta con ceros, calculo factores y resuelvo la fila
                if (fila_no_ok(i))
                {
                    //calculo de los factores para la fila "i"
                    int fila_referencia_para_calcular_factor = calcular_fila_referencia(i);
                    for (int j = 0; j < matriz_gaussiana_[i].size(); j++)
                    {
                        if (matriz_gaussiana_[i][j] == 0) continue;
                        else if (matriz_gaussiana_[i][j] != 0)
                        {
                            factor1 = matriz_gaussiana_[fila_referencia_para_calcular_factor][j];
                            factor2 = matriz_gaussiana_[i][j];
                            break;
                        }
                    }

                    //calculo de los nuevos valores de la fila "i" con los factores de la fila "i" calculados
                    for (int j = 0; j < matriz_gaussiana_[i].size(); j++)
                    {
                        matriz_gaussiana_[i][j] = factor1 * matriz_gaussiana_[i][j] - factor2 * matriz_gaussiana_[fila_referencia_para_calcular_factor][j];
                    }
                }
            }
            pintar_matriz();
        }
    }
    void resolver_sistema(void)
    {
        
    }
};

int main()
{
    int orden_sistema = 4;
    Gauss sistema_ecuaciones(orden_sistema);
    sistema_ecuaciones.solicitar_valores();
    sistema_ecuaciones.unir_matriz_con_terminos_independientes();
    sistema_ecuaciones.escalonar_matriz_gaussiana();
}
