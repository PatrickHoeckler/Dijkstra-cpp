#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;

class graph
{
    public:
        graph(char* filepath)
        {
            ifstream myFile;
            myFile.open(filepath);
            if (!myFile.is_open())
            {
                cout<<"Erro abrindo arquivo"<<endl;
                return;
            }
            int n=1;
            char c1,c2;
            c1='0';
            c2=' ';
            while(c1!='\n')
            {
                c1=(char)myFile.get();
                if (c1==' ')
                {
                    if (c2!=' ')
                        n++;
                }
                c2=c1;
                if (myFile.eof())
                    break;
            }
            if (n==1)
            {
                cout<<"O arquivo passado e invalido, ele precisa ser uma matriz quadrada de tamanho maior que 1"<<endl;
                myFile.close();
                return;
            }
            myFile.seekg(0,ios::beg);
            vector<vector<int> > m(n, vector<int>(n));
            for (unsigned int i=0;i<m.size();i++)
            {
                for (unsigned int j=0;j<m.back().size();j++)
                    myFile>>m[i][j];
            }
            edges=m;
            myFile.close();
            is_empty_bit=false;
        }

        bool is_empty()
        {
            return is_empty_bit;
        }
		
		unsigned int length() 
		{
			return (unsigned int)edges.size();
		}

        void print_graph()
        {
            cout<<"   ";
            for (unsigned int i=0;i<edges.size();i++)
                cout<<"   V"<<i<<"";
            cout<<endl;
            for (unsigned int i=0;i<edges.size();i++)
            {
                cout<<"V"<<i<<" |";
                for (unsigned int j=0;j<edges.back().size();j++)
                    cout<<setw(4)<<edges[i][j]<<" ";
                cout<<" |"<<endl;
            }
        }

        void dijkstra_algorithm(unsigned int o_vert)
        {
            if (o_vert>=edges.size())
            {
                cout<<"Esse vertice de origem nao esta no grafo"<<endl;
                return;
            }
            vector<int> dist(edges.size());
            vector<int> prev(edges.size());
            unsigned int i,j, h_size;
            for (i=0;i<dist.size();i++)
            {
                dist[i]=-1;
                prev[i]=-1;
            }
            dist[o_vert]=0;
            vector<int> H=dist;
            h_size=1;
            while(h_size!=0)
            {
                int minimo=0;
                for (j=1;j<H.size();j++)
                {
                    if (H[j]>=0 && (H[j]<H[minimo] || H[minimo]<0 ) )
                        minimo=j;
                }
                H[minimo]=-1;
                h_size--;
                for (j=0;j<edges.size();j++)
                {
                    if (edges[minimo][j]>=0)
                    {
                        if (dist[j]<0 || dist[j]>dist[minimo]+edges[minimo][j])
                        {
                            dist[j]=dist[minimo]+edges[minimo][j];
                            prev[j]=minimo;
                            if (H[j]<0)
                                h_size++;
                            H[j]=dist[j];
                        }
                    }
                }
            }
            cout<<"=========Arvore de Saida========="<<endl<<endl;
            cout<<"Vertice de origem - V"<<o_vert<<endl;
            for (i=0;i<prev.size();i++)
            {
                for (j=0;j<prev.size();j++)
                {
                    if(prev[j]==(int)i)
                    cout<<"{V"<<i<<"->V"<<j<<"} - custo de V"<<o_vert<<" a V"<<j<<"= "<<dist[j]<<endl;
                }
            }
        }

    private:
        vector<vector<int> > edges;
        bool is_empty_bit = true;
};

int main(int argc, char** args)
{
    if (argc==1)
    {
        cout<<"ERRO: O programa precisa de um arquivo .txt para funcionar. Passe o endereco do arquivo como argumento\n";
        return -1;
    }
    else if (argc>2)
    {
        cout<<"ERRO: O programa recebe apenas um argumento\n";
        return -1;
    }

    graph G(args[1]);
    if (G.is_empty())
        return -1;
    G.print_graph();
    cout<<endl;

    unsigned int o_vert;
    cout<<"Qual e o vertice de origem da arvore (0-"<<G.length() - 1<<"): ";
    cin>>o_vert;
    G.dijkstra_algorithm(o_vert);
    return 0;
}
