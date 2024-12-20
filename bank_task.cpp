#include <iostream>
#include <string>


using namespace std;

class BankAccount {
private:
    string accountNumber;
    string ownerName;
    double balance;

public:
    BankAccount(const string& accNum, const string& owner, double initialBalance)
        : accountNumber(accNum), ownerName(owner), balance(initialBalance) {}

    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Пополнен счет на " << amount << ". Текущий баланс: " << balance << endl;
        } else {
            cout << "Сумма пополнения должна быть положительной." << endl;
        }
    }


    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Снято " << amount << ". Текущий баланс: " << balance << endl;
        } else if (amount > balance) {
            cout << "Недостаточно средств для снятия." << endl;
        } else {
            cout << "Сумма снятия должна быть положительной." << endl;
        }
    }

 
    double getBalance() const {
        return balance;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:

    SavingsAccount(const string& accNum, const string& owner, double initialBalance, double rate)
        : BankAccount(accNum, owner, initialBalance), interestRate(rate) {}

 
    void applyInterest() {
        double interest = getBalance() * (interestRate / 100);
        deposit(interest);
        cout << "Начислены проценты: " << interest << ". Новый баланс: " << getBalance() << endl;
    }
};

int main() {

    BankAccount myAccount("123456", "Иван Иванов", 1000.0);
    myAccount.deposit(500);
    myAccount.withdraw(200);
    myAccount.withdraw(1500); 


    SavingsAccount mySavingsAccount("654321", "Петр Петров", 2000.0, 5.0);
    mySavingsAccount.deposit(300);
    mySavingsAccount.withdraw(100);
    mySavingsAccount.applyInterest(); 
    return 0;
}