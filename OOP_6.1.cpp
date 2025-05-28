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

    void copyString(char*& dest, const char* src) {
        if (src) {
            dest = new char[std::strlen(src) + 1];
            std::strcpy(dest, src);
        } else
            dest = nullptr;
    }

   public:
    Deposit(const char* acc, const char* cr, double rate, double amt, const char* last)
        : annualRate(rate), currentAmount(amt) {
        copyString(accountNumber, acc);
        copyString(creationDate, cr);
        copyString(lastInterestDate, last);
    }
    virtual ~Deposit() {
        delete[] accountNumber;
        delete[] creationDate;
        delete[] lastInterestDate;
    }
    Deposit(const Deposit& o) : annualRate(o.annualRate), currentAmount(o.currentAmount) {
        copyString(accountNumber, o.accountNumber);
        copyString(creationDate, o.creationDate);
        copyString(lastInterestDate, o.lastInterestDate);
    }
    Deposit& operator=(const Deposit& o) {
        if (this != &o) {
            delete[] accountNumber;
            delete[] creationDate;
            delete[] lastInterestDate;
            copyString(accountNumber, o.accountNumber);
            copyString(creationDate, o.creationDate);
            copyString(lastInterestDate, o.lastInterestDate);
            annualRate = o.annualRate;
            currentAmount = o.currentAmount;
        }
        return *this;
    }

    virtual void Print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Deposit& d) {
        d.Print(os);
        return os;
    }

    virtual Deposit* clone() const = 0;
};

class DemandDeposit : public Deposit {
   public:
    DemandDeposit(const char* acc, const char* cr, double r, double a, const char* last)
        : Deposit(acc, cr, r, a, last) {}
    void Print(std::ostream& os) const override {
        os << "DemandDeposit: acc=" << accountNumber << ", rate=" << annualRate
           << ", amt=" << currentAmount << "\n";
    }
    Deposit* clone() const override { return new DemandDeposit(*this); }
};

class ConditionalDeposit : public Deposit {
    char* condition;

   public:
    ConditionalDeposit(const char* acc, const char* cr, double r, double a, const char* last,
                       const char* cond)
        : Deposit(acc, cr, r, a, last) {
        copyString(condition, cond);
    }
    ~ConditionalDeposit() override { delete[] condition; }
    ConditionalDeposit(const ConditionalDeposit& o) : Deposit(o) {
        copyString(condition, o.condition);
    }
    ConditionalDeposit& operator=(const ConditionalDeposit& o) {
        Deposit::operator=(o);
        delete[] condition;
        copyString(condition, o.condition);
        return *this;
    }
    void Print(std::ostream& os) const override {
        os << "ConditionalDeposit: acc=" << accountNumber << ", condition=" << condition << "\n";
    }
    Deposit* clone() const override { return new ConditionalDeposit(*this); }
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

    Deposit* clone() const override { return new DemandDeposit(*this); }
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

    void Print(std::ostream& os) const override {
        os << "Type: Conditional Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nCondition: " << closingCondition
           << "\n";
    }

    Deposit* clone() const override { return new ConditionalDeposit(*this); }
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

    void Print(std::ostream& os) const override {
        os << "Type: Non-Withdrawable Term Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nDeposit term: " << depositTerm
           << " months"
           << "\nDeposit period: " << depositPeriod << " months\n";
    }

    Deposit* clone() const override { return new NonWithdrawableTermDeposit(*this); }
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
        if (rRate < 0) throw std::invalid_argument("Rate cannot be negative");
        if (iAmount < 0) throw std::invalid_argument("Amount cannot be negative");
    }

    void Print(std::ostream& os) const override {
        os << "Type: Withdrawable Term Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nDeposit term: " << depositTerm
           << " months"
           << "\nReduced rate: " << reducedRate << "%"
           << "\nInitial amount: $" << initialAmount << "\n";
    }

    Deposit* clone() const override { return new WithdrawableTermDeposit(*this); }
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