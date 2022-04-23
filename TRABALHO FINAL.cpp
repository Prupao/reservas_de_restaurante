#include <iostream>
#include <iomanip>
//#include <cstdbool>
using namespace std;

int contMesa = 0, contPrato = 0, contClient = 0, contFunc = 0, respCad, respRes, respRel,respEx = 0,somavalor,TotalGeral;//'respCad'= menu de cadastro || respRes = menu reserva.
float conta[50]; 
struct Data{
    int dia, mes, ano;
};
struct Cadastro{
    char prato[30], client[30], waiter[30];// 'prato' = nome do prato //'waiter' = nome do garçom
    int clIdade, mesaId, waiterId, clId, pratoId;//'clIdade' = idade do cliente// 'mesaId' = identificação da mesa // 'waiterId' = identificação do garçom // 'clId' = identificação do cliente
    float valor; //'valor' = preço do prato, 'cpf' = cpf do cliente || 'conta' = armazena a soma total de cada mesa || 
    bool reservada = false; //Todas as mesas começam SEM reserva -> 0 = false / 1 = true
};
struct Reserva{
  struct Data booking;
  int idBooking; //id da reserva
  //int status = 0; //livre = 0, ocupada = 1;
};
void menuPrincipal(int *op){
  cout<< "\e[1;1H\e[2J";
  cout<<"\n\t========== MENU PRINCIPAL ==========\n";
  cout<<"\n1- Cadastro\n2- Reservas\n3- Relatório\n4- Sair\n";
  cout<<"\n->Selecione uma das opções do menu: ";
  cin>> *op;
  fflush(stdin);
}
bool checkTable(int num, struct Cadastro *Registro){
  //table beeing used? false = 0, true = 1
  for(int i=0;i<num;++i){
    for(int j=i+1;j<num;++j){
      if(Registro[i].mesaId == Registro[j].mesaId){
        return true;
      }
    }
  }
  return 0;
}
bool checkMeal(int num, struct Cadastro *Registro){
  //MealId beein used? true = 1 false = 0
  for(int i=0;i<num;++i){
    for(int j=i+1;j<num;++j){
      if(Registro[i].pratoId==Registro[j].pratoId){
        return true;
      }
    }
  }
  return 0;
}
bool checkClient(int num, struct Cadastro *Registro){
  for(int i=0;i<num;++i){
    for(int j=i+1;j<num;++j){
      if(Registro[i].clId==Registro[j].clId){
        return true;
      }
    }
  }
  return 0;
}
bool checkStaff(int num, struct Cadastro *Registro){
  for(int i=0;i<num;++i){
    for(int j=i+1;j<num;++j){
      if(Registro[i].waiterId==Registro[j].waiterId)
      return true;
    }
  }
  return 0;
}
bool reservationClientCheck(struct Cadastro *Registro,int *IdCliente,int *contClient){
  for(int i=0;i<*contClient;++i){
    if(*IdCliente==Registro[i].clId||*IdCliente>0){
      return true;
    }
  }
  return 0;
}
bool reservationTableCheck(struct Cadastro *Registro,int *IdTable,int *contMesa){
  for(int i=0;i<*contMesa;++i){
    if(*IdTable==Registro[i].mesaId && Registro[i].reservada==false){
      return true;
    }
  } 
  return false;
}
bool reservationMealCheck(struct Cadastro *Registro,int *pedido,int *contPrato){
  for(int i=0;i<*contPrato;++i){
    if(*pedido==Registro[i].pratoId){
      return true;
    }
  }
  return 0;
}
void menuCadastro(struct Cadastro *Registro){
    respCad = 0;
    while(respCad != 5){
      int num, i; //'num' = qtd de repetições das instruções
      cout<<"\n\t>>>>>>>>>> MENU CADASTRO <<<<<<<<<<\n";
      cout<<"\n1- Cadastrar mesa\n2- Cadastrar pratos\n3- Cadastrar cliente\n4- Cadastrar funcionário\n5- Voltar ao menu principal\n";
      cout<<"\n-> Selecione uma das opções do menu acima: ";
      cin>> respCad;
      fflush(stdin);
      switch(respCad){
          //Cadastro mesa
          case 1: 
              cout<<"\e[1;1H\e[2J";
              cout<<"\nOpção 'Cadastrar mesa' selecionada...\n";
              cout<< "\nExistem " << contMesa << " mesas cadastradas.\n";
              cout<<"\nQuantas mesas deseja cadastrar: ";
              cin>> num;
              fflush(stdin);
              for(i = contMesa; i < num; i++){
                cout<<"\n->Informe o cód. de identificação da "<< contMesa+1 << ".a mesa: ";
                cin>>Registro[i].mesaId;
                fflush(stdin);
                if(checkTable(num, Registro) == true){
                  cout<< "\n\t>>Código de mesa já em uso!<<\n";
                  break;
                }
                contMesa++;
              }
              // TESTAR CADASTRO
              for(int i = 0; i < contMesa; i++){
                  cout<<"\nMesa: " <<Registro[i].mesaId << "\nStatus: "<< Registro[i].reservada << endl;
              }
              //
            break;//end_add table
          case 2: //Cadastro prato
              cout<<"\e[1;1H\e[2J";
              cout<<"\nOpção 'Cadastrar prato' selecionada...\n";
              cout<< "\nExistem " << contPrato << " pratos cadastradas.\n";
              cout<<"\nQuantos pratos deseja cadastrar: ";
              cin>> num;
              fflush(stdin);
              for(i = contPrato; i < num; i++){
                cout<<"\n->Informe o nome do prato: ";
                cin>> Registro[i].prato;
                cout<<"\n->Agora entre com o valor do prato: ";
                cin>> Registro[i].valor;
                cout<<"\n->Entre com o Id do prato: ";
                cin>> Registro[i].pratoId;
                if(checkMeal(num, Registro) == true){
                  break;
                }
                contPrato++;
              }
            break;//end_add_main/starter_course
        case 3: //Cadastrar cliente
          cout<< "\e[1;1H\e[2J";
          cout<<"\nOpção 'Cadastrar cliente' selecionada...\n";
          cout<< "\nExistem " << contClient << " clientes cadastrados.\n";
          cout<<"\nQuantos clientes deseja cadastrar: ";
          cin>> num;
          fflush(stdin);
          for(i = contClient; i < num; i++){
            cout<< "\n->Informe o nome do cliente: ";
            cin>> Registro[i].client;
            cout<< "\n->Informe a idade do cliente: ";
            cin>> Registro[i].clIdade;
            fflush(stdin);
            if(Registro[i].clIdade < 18){
              cout << "\n\t>>Bebidas alcoólicas não são permitidas!<<\n";
            } 
            cout<< "\n->Agora indique o cód.ID do cliente: ";
            cin>> Registro[i].clId;
            if(checkClient(num, Registro) == true){
              break;
            }
            contClient++;
          }
          break;//end_add client
        case 4: //Cadastrar garçom
          cout<< "\e[1;1H\e[2J";
          cout<<"\nOpção 'Cadastrar Garçom' selecionada...\n";
          cout<< "\nExistem " << contFunc << " Garçons cadastrados.\n";
          cout<<"\nQuantos garçons deseja cadastrar: ";
          cin>> num;
          fflush(stdin);
          for(i = contFunc; i < num; i++){
            cout<< "\n->Informe o nome do Garçon: ";
            cin>> Registro[i].waiter;
            fflush(stdin);
            cout<< "\n->Agora informe o ID do Garçon: ";
            cin>> Registro[i].waiterId;
            if(checkStaff(num, Registro) == true){
              break;
            }
            contFunc++;
          }
          break; //end_add waiter
        case 5: //back to main menu
          cout<< "\e[1;1H\e[2J";
          break;
      }//end_switch
    }//end_while
}//end_MenuCadastro

//Menu Reserva
int menuReserva(struct Cadastro *Registro, struct Reserva *Reservation){
    respRes = 0;
    int pedido; //Escolher o prato
    int freeTable;//Qual mesa vai liberar
    int bookingClId[100],bookingMeId[100],bookingV[100],bookingTbId[100],contBook=0;
  while(respRes != 3){
    int IdCliente, IdTable; //'IdCliente' = verifica qual cliente está reservando || 'IdTable' = escolhe a mesa
    cout<<"\n\t>>>>>>>>>> MENU RESERVA <<<<<<<<<<\n";
    cout<<"\n1- Reservar mesa\n2- Liberar reserva (conta)\n3- Voltar ao menu principal\n";
    cout<<"\n-> Selecione uma das opções do menu acima: ";
    cin>> respRes;
    fflush(stdin);
    switch(respRes){
        case 1: //booking_table
          cout<<"\e[1;1H\e[2J";
          cout<<"\nOpção 'Reservar mesa' selecionada...\n";
          cout<<"\n->Informe o ID do cliente: ";
          cin>>IdCliente;
          fflush(stdin);
          //Verifica cliente
          if(reservationClientCheck(Registro,&IdCliente,&contClient) == true){
            cout<<"\e[1;1H\e[2J";
            cout<<"\nCliente identificado...\n";
            bookingClId[contBook]=IdCliente;
          }else{
            cout<<"\n!!ID de cliente não identificado!!\n";
            return 0;
          }
          //Exibe as mesas cadastradas DISPONÍVEIS
          cout<<"\nA ID das mesas disponíveis são:\n";
          for(int i = 0; i < contMesa; i++){
            if(Registro[i].reservada == 0){
              cout<<"\n- " <<Registro[i].mesaId << endl;
            }
          }
          cout<<"\n->Informe a mesa que deseja reservar: ";
          cin >> IdTable;
          fflush(stdin);
          //Verifica mesa disponível
          for(int i = 0; i < contMesa; i++){
            if(IdTable == Registro[i].mesaId && Registro[i].reservada == false){
              bookingTbId[contBook]=IdTable;
              cout<<"\nMesa DISPONÍVEL!\n";
              Registro[i].reservada = true;
                break;
            }else if(reservationTableCheck(Registro,&IdTable, &contMesa)==false){
              cout<<"\nMesa NÃO disponível ou NÃO cadastrada!\n";
                return 0;
            }
          }
          //Reservar os pratos da mesa
          cout<<"\n\t>>>>> CARDÁPIO <<<<<\n";
          for(int i = 0; i < contPrato; i++){
            cout<<"\n| "<< Registro[i].pratoId << " | " << Registro[i].prato << "| R$ " <<Registro[i].valor << endl;
          }
          if(contPrato == 0){
            cout<<"\n!!Nenhum prato foi cadastrado ainda!!\n";
          }
          cout<<"\n->Informe o ID do prato que deseja pedir: \n";
          cin>> pedido;
          fflush(stdin);
          if(reservationMealCheck(Registro,&pedido,&contPrato)==false){
            cout<<"!!Pedido INVÁLIDO!!";
            return 0;
          }else if(reservationMealCheck(Registro,&pedido,&contPrato)==true){
            bookingMeId[contBook]=pedido;
            cout<<"Pedido selecionado com SUCESSO"<<endl;
            for(int i=0;i<contPrato;++i){
              if(pedido==Registro[i].pratoId)
              bookingV[contBook]=Registro[i].valor;
              break;
            }
          }
          /*
          // Armazena o valor total da conta num vetor
          for(int i = 0; i < contMesa; i++){
            bookingMeId[contBook]=pedido;
            if(pedido==Registro[i].pratoId && IdTable == Registro[i].mesaId){
              conta[i] = bookingV[contBook]/*Registro[i].valor;
              TotalGeral = TotalGeral + conta[i]; 
                break;
            }
          }
          */
          // TESTAR RESREVA DE PRATOS
          for(int i=0;i<contBook;++i){ 
            cout<<"\nMesa: "<< bookingTbId[i] << "\nValor total: " << bookingV[i] << "\nCliente: "<<bookingClId[i]<<endl;
          }
          //
          break;//end_booking
        case 2: //free_table_bill  
          cout<<"\e[1;1H\e[2J";
          cout<<"\nOpção 'Liberar reserva' selecionada...\n";
          cout<<"\n->As mesas ocupadas são: \n";
          for(int i = 0; i < contMesa; i++){
            if(Registro[i].reservada == true){
              cout<<"\n\t- Mesa: " << Registro[i].mesaId << endl;
            }
          }
          cout<<"\n->Informe qual mesa deseja liberar: \n";
          cin>> freeTable;
          fflush(stdin);
          for(int i = 0; i < contMesa; i++){
            if(freeTable == Registro[i].mesaId && Registro[i].reservada == true){
              cout<<"\n->Mesa LIBERADA...\n";
              Registro[i].reservada = false;
              cout<<"\nA conta teve o valor de R$: "<< conta[i] << endl;
              conta[i] = 0; 
                break;
            }
          }
          break;//end_free_table_bill
    return 0;
        case 3: //return_menu
          break;
    }//end_switch_respRes
  } //end_while
  return 0;
} //end_MenuReserva

//Menu Relatório
void menuRelatorio(struct Cadastro *Registro, struct Reserva *Reservation){
  respRel = 0;
  while(respRel != 3){
    cout<<"\n\t>>>>>>>>>> MENU RELATÓRIO <<<<<<<<<<\n";
    cout<<"\n1- Resultado financeiro\n2- Exibir registros\n3- Voltar ao menu principal\n";
    cout<<"\n-> Selecione uma das opções do menu acima: ";
    cin>> respRel;
    fflush(stdin);
    switch(respRel){
      case 1: //resultado financeiro
          cout<< "\n A soma total das mesas é: " << TotalGeral << endl;
          break;
        break;//end_resultado financeiro
      case 2: //inicio exibição //escolhe as opções do menu exibir
        while(respEx != 5){
          cout<<"\n\t>>>>>>>>>> MENU EXIBIR <<<<<<<<<<\n";
          cout<<"\n1- Exibir todas as mesas\n2- Exibir todos os pratos\n3- Exibir todos os clientes\n4- Exibir todos os funcionários\n5- Voltar ao menu relatório\n";
          cout<<"\n-> Selecione uma das opções do menu acima: ";
          cin>> respEx;
          fflush(stdin);
          switch(respEx){
            case 1: //Exibir todas as mesas
              cout<<"\e[1;1H\e[2J";
              cout<<"\nOpção 'Exibir todas as mesas' selecionada...\n";
              for(int i = 0; i < contMesa; i ++){
                cout<<"\n->Id de mesa: \n"<< Registro[i].mesaId << endl;
              }
              cout<<"\n\t->Foram cadastradas "<< contMesa <<" mesas no total.\n";
              break;//end_show_tables
            case 2: //Exibir todos os pratos
              cout<<"\e[1;1H\e[2J";
              cout<<"\nOpção 'Exibir todos os pratos' selecionada...\n";
              for(int i = 0; i < contPrato; i ++){
                cout <<"\nA quantidade de prato é: "<<contPrato<< endl;
              }
              break;//end_show courses
            case 3: //Exibir todos os clientes
              cout<<"\e[1;1H\e[2J";
              cout<<"\nOpção 'Exibir todos os clientes' selecionada...\n";
              for(int i = 0; i < contClient; i ++){
                cout << "\nA quantidade de clientes é: "<<contClient<< endl;
              }
              break;//end_showallcustomers
            case 4: //Exibir funcionários
              cout<<"\e[1;1H\e[2J";
              cout<<"\nOpção 'Exibir funcionários' selecionada...\n";
              for(int i = 0; i < contFunc; i ++){
                cout << "\nA quantidade de funcionários é: "<<contFunc << endl;
              }
              break;//end_showallemployees
            case 5: //sair
              break;//end_exit
          }
        }
          break;// final exibição
      case 3: //sair do menu relatório
          break;//end_exitmenurelatorio
    }
  } 
}//end_MenuRelatorio

int main(){
    struct Cadastro Registro;
    struct Reserva Reservation;
    int op; //'op'= opção de menu;

    while(op != 4){
      menuPrincipal(&op);
      switch(op){
        case 1: //MenuCadastro
          menuCadastro(&Registro);
            break;//end_MenuCadastro
        case 2: //MenuReserva
          menuReserva(&Registro, &Reservation);
            break;//end_MenuReserva
        case 3:
          menuRelatorio(&Registro, &Reservation);
        break;
        case 4:
        break;
    }
  }
  return 0;
}
