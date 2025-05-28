#include <cstddef>
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
    virtual void printInfo() const = 0;
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

    void printInfo() const override { Print(std::cout); }
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

    ~ConditionalDeposit() override { delete[] closingCondition; }

    ConditionalDeposit(const ConditionalDeposit& o) : Deposit(o) {
        copyString(closingCondition, o.closingCondition);
    }
    ConditionalDeposit& operator=(const ConditionalDeposit& o) {
        if (this != &o) {
            Deposit::operator=(o);
            delete[] closingCondition;
            copyString(closingCondition, o.closingCondition);
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

    void printInfo() const override { Print(std::cout); }
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

    void Print(std::ostream& os) const override {
        os << "Term Deposit: " << depositTerm << " months\n";
    }

    void printInfo() const override { Print(std::cout); }
    Deposit* clone() const override { return new TermDeposit(*this); }
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
           << " months\nDeposit period: " << depositPeriod << " months\n";
    }

    void printInfo() const override { Print(std::cout); }
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
           << " months\nReduced rate: " << reducedRate << "%\nInitial amount: $" << initialAmount
           << "\n";
    }

    void printInfo() const override { Print(std::cout); }
    Deposit* clone() const override { return new WithdrawableTermDeposit(*this); }
};

template <typename T>
class OwnedLinkedList {
   private:
    struct Node {
        T* data;
        Node* next;
        Node(T* d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* head;

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp->data;
            delete temp;
        }
    }

   public:
    OwnedLinkedList() : head(nullptr) {}

    ~OwnedLinkedList() { clear(); }

    OwnedLinkedList(const OwnedLinkedList& other) : head(nullptr) {
        Node** current = &head;
        for (Node* n = other.head; n; n = n->next) {
            *current = new Node(n->data->clone());
            current = &((*current)->next);
        }
    }

    OwnedLinkedList& operator=(const OwnedLinkedList& other) {
        if (this != &other) {
            clear();
            Node** current = &head;
            for (Node* n = other.head; n; n = n->next) {
                *current = new Node(n->data->clone());
                current = &((*current)->next);
            }
        }
        return *this;
    }

    OwnedLinkedList(OwnedLinkedList&& other) noexcept : head(other.head) { other.head = nullptr; }

    OwnedLinkedList& operator=(OwnedLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }

    void add(T* data) { head = new Node(data, head); }

    void remove(T* data) {
        Node** curr = &head;
        while (*curr) {
            if ((*curr)->data == data) {
                Node* temp = *curr;
                *curr = temp->next;
                delete temp->data;
                delete temp;
                return;
            }
            curr = &((*curr)->next);
        }
    }

    void printAll() const {
        for (Node* n = head; n; n = n->next) {
            n->data->printInfo();
            std::cout << "-----\n";
        }
    }

    void clearList() {
        clear();
        head = nullptr;
    }
};

int main() {
    OwnedLinkedList<Deposit> list;

    list.add(new DemandDeposit("ACC001", "2024-01-01", 5.0, 1000.0, "2024-06-01"));
    list.add(
        new ConditionalDeposit("ACC002", "2023-05-01", 4.2, 2500.0, "2024-06-01", "After wedding"));
    list.add(new TermDeposit("ACC003", "2021-06-15", 7.0, 5000.0, "2024-06-01", 12));
    list.add(
        new NonWithdrawableTermDeposit("ACC004", "2020-07-01", 6.8, 10000.0, "2024-06-01", 24, 6));
    list.add(new WithdrawableTermDeposit("ACC005", "2022-08-10", 6.5, 8000.0, "2024-06-01", 18, 4.5,
                                         6000.0));

    std::cout << "Original list:\n";
    list.printAll();

    OwnedLinkedList<Deposit> copyList = list;
    std::cout << "\nCopied list:\n";
    copyList.printAll();

    OwnedLinkedList<Deposit> movedList = std::move(list);
    std::cout << "\nMoved list:\n";
    movedList.printAll();

    std::cout << "\nAfter move, original list should be empty:\n";
    list.printAll();

    copyList.clearList();
    movedList.clearList();
    std::cout << "\nAll lists cleared successfully.\n";

    std::cin.ignore();
    std::cin.get();
    return 0;
}
