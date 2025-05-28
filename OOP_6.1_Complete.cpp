#include <cstring>
#include <iostream>
#include <stdexcept>

class Deposit {
   protected:
    char* accountNumber;
    char* creationDate;
    double annualRate;
    double currentAmount;
    char* lastInterestDate;

    void copyString(char*& dest, const char* source) {
        if (source) {
            dest = new char[strlen(source) + 1];
            strcpy(dest, source);
        } else {
            dest = nullptr;
        }
    }

   public:
    Deposit(const char* accNum, const char* crDate, double rate, double amount,
            const char* lastDate)
        : annualRate(rate), currentAmount(amount) {
        copyString(accountNumber, accNum);
        copyString(creationDate, crDate);
        copyString(lastInterestDate, lastDate);

        if (annualRate < 0) throw std::invalid_argument("Rate cannot be negative");
        if (currentAmount < 0) throw std::invalid_argument("Amount cannot be negative");
    }

    virtual ~Deposit() {
        delete[] accountNumber;
        delete[] creationDate;
        delete[] lastInterestDate;
    }

    Deposit(const Deposit& other) {
        copyString(accountNumber, other.accountNumber);
        copyString(creationDate, other.creationDate);
        copyString(lastInterestDate, other.lastInterestDate);
        annualRate = other.annualRate;
        currentAmount = other.currentAmount;
    }

    Deposit& operator=(const Deposit& other) {
        if (this != &other) {
            delete[] accountNumber;
            delete[] creationDate;
            delete[] lastInterestDate;

            copyString(accountNumber, other.accountNumber);
            copyString(creationDate, other.creationDate);
            copyString(lastInterestDate, other.lastInterestDate);
            annualRate = other.annualRate;
            currentAmount = other.currentAmount;
        }
        return *this;
    }

    virtual void Print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Deposit& deposit) {
        deposit.Print(os);
        return os;
    }
};

class DemandDeposit : public Deposit {
   public:
    DemandDeposit(const char* accNum, const char* crDate, double rate, double amount,
                  const char* lastDate)
        : Deposit(accNum, crDate, rate, amount, lastDate) {}

    void Print(std::ostream& os) const override {
        os << "Type: Demand Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\n";
    }
};

class ConditionalDeposit : public Deposit {
    char* closingCondition;

   public:
    ConditionalDeposit(const char* accNum, const char* crDate, double rate, double amount,
                       const char* lastDate, const char* condition)
        : Deposit(accNum, crDate, rate, amount, lastDate) {
        copyString(closingCondition, condition);
    }

    ~ConditionalDeposit() { delete[] closingCondition; }

    ConditionalDeposit(const ConditionalDeposit& other) : Deposit(other) {
        copyString(closingCondition, other.closingCondition);
    }

    ConditionalDeposit& operator=(const ConditionalDeposit& other) {
        if (this != &other) {
            Deposit::operator=(other);
            delete[] closingCondition;
            copyString(closingCondition, other.closingCondition);
        }
        return *this;
    }

    void Print(std::ostream& os) const override {
        os << "Type: Conditional Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nCondition: " << closingCondition
           << "\n";
    }
};

class TermDeposit : public Deposit {
   protected:
    int depositTerm;

   public:
    TermDeposit(const char* accNum, const char* crDate, double rate, double amount,
                const char* lastDate, int term)
        : Deposit(accNum, crDate, rate, amount, lastDate), depositTerm(term) {
        if (term <= 0) throw std::invalid_argument("Term must be positive");
    }

    TermDeposit(const TermDeposit& other) : Deposit(other), depositTerm(other.depositTerm) {}

    TermDeposit& operator=(const TermDeposit& other) {
        if (this != &other) {
            Deposit::operator=(other);
            depositTerm = other.depositTerm;
        }
        return *this;
    }

    void Print(std::ostream& os) const override { os << "Term: " << depositTerm << " months\n"; }
};

class NonWithdrawableTermDeposit : public TermDeposit {
    int depositPeriod;

   public:
    NonWithdrawableTermDeposit(const char* accNum, const char* crDate, double rate, double amount,
                               const char* lastDate, int term, int period)
        : TermDeposit(accNum, crDate, rate, amount, lastDate, term), depositPeriod(period) {
        if (period <= 0) throw std::invalid_argument("Period must be positive");
    }

    NonWithdrawableTermDeposit(const NonWithdrawableTermDeposit& other)
        : TermDeposit(other), depositPeriod(other.depositPeriod) {}

    NonWithdrawableTermDeposit& operator=(const NonWithdrawableTermDeposit& other) {
        if (this != &other) {
            TermDeposit::operator=(other);
            depositPeriod = other.depositPeriod;
        }
        return *this;
    }

    void Print(std::ostream& os) const override {
        os << "Type: Non-Withdrawable Term Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nDeposit term: " << depositTerm
           << " months\nDeposit period: " << depositPeriod << " months\n";
    }
};

class WithdrawableTermDeposit : public TermDeposit {
    double reducedRate;
    double initialAmount;

   public:
    WithdrawableTermDeposit(const char* accNum, const char* crDate, double rate, double amount,
                            const char* lastDate, int term, double rRate, double iAmount)
        : TermDeposit(accNum, crDate, rate, amount, lastDate, term),
          reducedRate(rRate),
          initialAmount(iAmount) {
        if (rRate < 0) throw std::invalid_argument("Reduced rate cannot be negative");
        if (iAmount < 0) throw std::invalid_argument("Initial amount cannot be negative");
    }

    WithdrawableTermDeposit(const WithdrawableTermDeposit& other)
        : TermDeposit(other), reducedRate(other.reducedRate), initialAmount(other.initialAmount) {}

    WithdrawableTermDeposit& operator=(const WithdrawableTermDeposit& other) {
        if (this != &other) {
            TermDeposit::operator=(other);
            reducedRate = other.reducedRate;
            initialAmount = other.initialAmount;
        }
        return *this;
    }

    void Print(std::ostream& os) const override {
        os << "Type: Withdrawable Term Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nDeposit term: " << depositTerm
           << " months\nReduced rate: " << reducedRate << "%\nInitial amount: $" << initialAmount
           << "\n";
    }
};

int main() {
    Deposit* deposits[] = {
        new DemandDeposit("ACC001", "2025-05-01", 5.0, 10000, "2033-12-31"),
        new ConditionalDeposit("ACC002", "2029-02-15", 4.5, 50000, "2033-12-31", "Until marriage"),
        new NonWithdrawableTermDeposit("ACC003", "2073-03-10", 7.0, 100000, "2105-12-31", 24, 6),
        new WithdrawableTermDeposit("ACC004", "2053-04-20", 6.5, 200000, "2084-12-31", 12, 3.0,
                                    200000)};

    for (auto* deposit : deposits) {
        std::cout << *deposit << "------------------------\n";
        delete deposit;
    }

    std::cin.ignore();
    std::cin.get();
    return 0;
}
