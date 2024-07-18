/*************************************************************
**************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
**************************************************************
*************************************************************/

#include <string>
#include "random.h"

using namespace std;

double Prezzo(double Z){ //Funzione che genera i prezzi S(T).
   double t=0.01; //Lunghezza dell'intervallino di tempo.
   double rate=0.1; //Interesse.
   double vol=0.25; //Volatilità.
   
   double coef; //Lo calcolo una volta sola.    
   coef = rate-0.5*vol*vol;
   
   return exp((coef)*t+Z*vol*sqrt(t));     
}

double Call(double S){ //Calcola il guadagno finale per la Call.
   double K=100.0; //Prezzo a cui vorrei comprare.     
   double T=1.0; //Tempo finale.
   double rate=0.1; //Interesse.
   
   double coef; //Lo calcolo una volta sola.    
   coef = exp(-rate*T);

   if(S>K) return coef*(S-K);
   else return 0;
}

double Put(double S){ //Calcola il guadagno finale per la Put.
   double K=100.0; //Prezzo a cui vorrei comprare.     
   double T=1.0; //Tempo finale.
   double rate=0.1; //Interesse.
   
   double coef; //Lo calcolo una volta sola.    
   coef = exp(-rate*T);

   if(K>S) return coef*(K-S);
   else return 0;
}


int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
     Primes >> p1 >> p2 ;
	 Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

   int i, j; //Contatori.
   double Z; //Variabile estratta in N(0,1).     
   //double si; //Prezzo che cresce ad ogni intervallino. All'inizio, t=0, è 100
   
   double S; //Prezzo che vorrei calcolare.
   double C; //Guadagno per l'opzione Call.
   //double P; //Guadagno per l'opzione Put.
   
   for(i=0; i<10; i++){  //Genero 10 prezzi.
      S = 100.0; //Ad ogni ciclo imposto il prezzo iniziale.
	             //Sarà modificato intervallo dopo intervallo, per 100 volte.
      for(j=0; j<100; j++){ //Divido l'intervallo in 100 intervallini. 

	     Z = rnd.Gauss(0,1); //Estraggo la variabile Z nell'intervallo i-esimo.
	     S = S*Prezzo(Z); //Calcolo il prezzo nell'intervallo i-esimo e assegno
                          //ogni volta il valore del prezzo dello step precedente.
		 //Si sommano così tutti i prezzi e si ottiene il prezzo al tempo finale T=1.						
	  } 
	  
	  C = Call(S); //Calcolo il guadagno Call.
      cout << S << "  " << C << endl;
      //P = Put(S); //Calcolo il guadagno Put.
      //cout << S << "  " << P << endl;     
   }
   
   rnd.SaveSeed();
   return 0;
}

/*************************************************************
**************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
**************************************************************
*************************************************************/
