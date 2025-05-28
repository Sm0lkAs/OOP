#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class Deposit {
   protected:
    char* accountNumber;
    char* creationDate;
    double annualRate;
    double currentAmount;
    char* lastInterestDate;

    void copyString(char*& dest, const char* source) {
        if (source) {
            dest = new char[std::strlen(source) + 1];
            std::strcpy(dest, source);
        } else
            dest = nullptr;
    }

   public:
    Deposit(const char* accNum = "", const char* crDate = "", double rate = 0.0,
            double amount = 0.0, const char* lastDate = "")
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

    Deposit(Deposit&& o) noexcept
        : accountNumber(o.accountNumber),
          creationDate(o.creationDate),
          annualRate(o.annualRate),
          currentAmount(o.currentAmount),
          lastInterestDate(o.lastInterestDate) {
        o.accountNumber = o.creationDate = o.lastInterestDate = nullptr;
    }

    Deposit& operator=(Deposit&& o) noexcept {
        if (this != &o) {
            delete[] accountNumber;
            delete[] creationDate;
            delete[] lastInterestDate;
            accountNumber = o.accountNumber;
            creationDate = o.creationDate;
            lastInterestDate = o.lastInterestDate;
            annualRate = o.annualRate;
            currentAmount = o.currentAmount;
            o.accountNumber = o.creationDate = o.lastInterestDate = nullptr;
        }
        return *this;
    }

    virtual void Print(std::ostream& os) const = 0;
    virtual Deposit* Clone() const = 0;
    virtual void Serialize(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Deposit& d) {
        d.Print(os);
        return os;
    }
};

class DemandDeposit : public Deposit {
   public:
    DemandDeposit(const char* acc, const char* cr, double r, double amt, const char* last)
        : Deposit(acc, cr, r, amt, last) {}

    DemandDeposit* Clone() const override { return new DemandDeposit(*this); }

    void Print(std::ostream& os) const override {
        os << "DemandDeposit " << accountNumber << ' ' << creationDate << ' ' << annualRate << ' '
           << currentAmount << ' ' << lastInterestDate;
    }

    void Serialize(std::ostream& os) const override { Print(os); }
};

class ConditionalDeposit : public Deposit {
    char* condition;

   public:
    ConditionalDeposit(const char* acc, const char* cr, double r, double amt, const char* last,
                       const char* cond)
        : Deposit(acc, cr, r, amt, last) {
        copyString(condition, cond);
    }

    ~ConditionalDeposit() override { delete[] condition; }

    ConditionalDeposit(const ConditionalDeposit& o) : Deposit(o) {
        copyString(condition, o.condition);
    }

    ConditionalDeposit& operator=(const ConditionalDeposit& o) {
        if (this != &o) {
            Deposit::operator=(o);
            delete[] condition;
            copyString(condition, o.condition);
        }
        return *this;
    }

    ConditionalDeposit(ConditionalDeposit&& o) noexcept
        : Deposit(std::move(o)), condition(o.condition) {
        o.condition = nullptr;
    }

    ConditionalDeposit& operator=(ConditionalDeposit&& o) noexcept {
        if (this != &o) {
            Deposit::operator=(std::move(o));
            delete[] condition;
            condition = o.condition;
            o.condition = nullptr;
        }
        return *this;
    }

    ConditionalDeposit* Clone() const override { return new ConditionalDeposit(*this); }

    void Print(std::ostream& os) const override {
        os << "ConditionalDeposit " << accountNumber << ' ' << creationDate << ' ' << annualRate
           << ' ' << currentAmount << ' ' << lastInterestDate << ' ' << condition;
    }

    void Serialize(std::ostream& os) const override { Print(os); }
};

class TermDeposit : public Deposit {
   protected:
    int depositTerm;

   public:
    TermDeposit(const char* acc, const char* cr, double r, double amt, const char* last, int term)
        : Deposit(acc, cr, r, amt, last), depositTerm(term) {
        if (term <= 0) throw std::invalid_argument("Term must be positive");
    }

    TermDeposit* Clone() const override { return new TermDeposit(*this); }

    void Print(std::ostream& os) const override {
        os << "TermDeposit " << accountNumber << ' ' << creationDate << ' ' << annualRate << ' '
           << currentAmount << ' ' << lastInterestDate << ' ' << depositTerm;
    }

    void Serialize(std::ostream& os) const override { Print(os); }
};

class NonWithdrawableTermDeposit : public TermDeposit {
    int depositPeriod;

   public:
    NonWithdrawableTermDeposit(const char* acc, const char* cr, double r, double amt,
                               const char* last, int term, int period)
        : TermDeposit(acc, cr, r, amt, last, term), depositPeriod(period) {
        if (period <= 0) throw std::invalid_argument("Period must be positive");
    }

    NonWithdrawableTermDeposit* Clone() const override {
        return new NonWithdrawableTermDeposit(*this);
    }

    void Print(std::ostream& os) const override {
        os << "NonWithdrawableTermDeposit " << accountNumber << ' ' << creationDate << ' '
           << annualRate << ' ' << currentAmount << ' ' << lastInterestDate << ' ' << depositTerm
           << ' ' << depositPeriod;
    }

    void Serialize(std::ostream& os) const override { Print(os); }
};

class WithdrawableTermDeposit : public TermDeposit {
    double reducedRate;
    double initialAmount;

   public:
    WithdrawableTermDeposit(const char* acc, const char* cr, double r, double amt, const char* last,
                            int term, double rRate, double iAmt)
        : TermDeposit(acc, cr, r, amt, last, term), reducedRate(rRate), initialAmount(iAmt) {
        if (rRate < 0) throw std::invalid_argument("Reduced rate cannot be negative");
        if (iAmt < 0) throw std::invalid_argument("Initial amount cannot be negative");
    }

    WithdrawableTermDeposit* Clone() const override { return new WithdrawableTermDeposit(*this); }

    void Print(std::ostream& os) const override {
        os << "WithdrawableTermDeposit " << accountNumber << ' ' << creationDate << ' '
           << annualRate << ' ' << currentAmount << ' ' << lastInterestDate << ' ' << depositTerm
           << ' ' << reducedRate << ' ' << initialAmount;
    }

    void Serialize(std::ostream& os) const override { Print(os); }
};

Deposit* CreateDepositFromStream(std::istream& is) {
    std::string type;
    if (!(is >> type)) return nullptr;
    if (type == "DemandDeposit") {
        std::string acc, cr, last;
        double r, amt;
        is >> acc >> cr >> r >> amt >> last;
        return new DemandDeposit(acc.c_str(), cr.c_str(), r, amt, last.c_str());
    }
    if (type == "ConditionalDeposit") {
        std::string acc, cr, last, cond;
        double r, amt;
        is >> acc >> cr >> r >> amt >> last;
        std::getline(is, cond);
        if (!cond.empty() && cond[0] == ' ') cond.erase(0, 1);
        return new ConditionalDeposit(acc.c_str(), cr.c_str(), r, amt, last.c_str(), cond.c_str());
    }
    if (type == "TermDeposit") {
        std::string acc, cr, last;
        int term;
        double r, amt;
        is >> acc >> cr >> r >> amt >> last >> term;
        return new TermDeposit(acc.c_str(), cr.c_str(), r, amt, last.c_str(), term);
    }
    if (type == "NonWithdrawableTermDeposit") {
        std::string acc, cr, last;
        int term, period;
        double r, amt;
        is >> acc >> cr >> r >> amt >> last >> term >> period;
        return new NonWithdrawableTermDeposit(acc.c_str(), cr.c_str(), r, amt, last.c_str(), term,
                                              period);
    }
    if (type == "WithdrawableTermDeposit") {
        std::string acc, cr, last;
        int term;
        double r, amt, rRate, iAmt;
        is >> acc >> cr >> r >> amt >> last >> term >> rRate >> iAmt;
        return new WithdrawableTermDeposit(acc.c_str(), cr.c_str(), r, amt, last.c_str(), term,
                                           rRate, iAmt);
    }
    return nullptr;
}

class DepositArray {
    Deposit** data;
    size_t size;
    size_t capacity;
    void resize(size_t newCap) {
        Deposit** nd = new Deposit*[newCap];
        for (size_t i = 0; i < size; ++i) nd[i] = data[i];
        delete[] data;
        data = nd;
        capacity = newCap;
    }

   public:
    DepositArray() : data(nullptr), size(0), capacity(0) {}

    DepositArray(const DepositArray& other) : size(other.size), capacity(other.capacity) {
        data = new Deposit*[capacity];
        for (size_t i = 0; i < size; ++i) data[i] = other.data[i]->Clone();
    }

    DepositArray& operator=(const DepositArray& other) {
        if (this != &other) {
            for (size_t i = 0; i < size; ++i) delete data[i];
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new Deposit*[capacity];
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i]->Clone();
        }
        return *this;
    }

    DepositArray(DepositArray&& other) noexcept
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = other.capacity = 0;
    }

    DepositArray& operator=(DepositArray&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < size; ++i) delete data[i];
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = other.capacity = 0;
        }
        return *this;
    }

    ~DepositArray() {
        for (size_t i = 0; i < size; ++i) delete data[i];
        delete[] data;
    }

    void add(const Deposit& d) {
        if (size == capacity) resize(capacity ? capacity * 2 : 1);
        data[size++] = d.Clone();
    }

    void remove(size_t idx) {
        if (idx >= size) throw std::out_of_range("Index out of range");
        delete data[idx];
        for (size_t i = idx; i + 1 < size; ++i) data[i] = data[i + 1];
        --size;
    }

    void printAll(std::ostream& os) const {
        for (size_t i = 0; i < size; ++i) os << *data[i] << "\n";
    }

    void save(const std::string& fn) const {
        std::ofstream ofs(fn);
        ofs << size << "\n";
        for (size_t i = 0; i < size; ++i) {
            data[i]->Serialize(ofs);
            ofs << "\n";
        }
    }

    void load(const std::string& fn) {
        std::ifstream ifs(fn);
        if (!ifs) return;
        size_t n;
        ifs >> n;
        std::string line;
        std::getline(ifs, line);
        for (size_t i = 0; i < n; ++i) {
            std::getline(ifs, line);
            std::istringstream iss(line);
            Deposit* d = CreateDepositFromStream(iss);
            if (d) {
                add(*d);
                delete d;
            }
        }
    }
};

int main() {
    const std::string filename = "deposits.txt";

    DepositArray arr;
    arr.add(DemandDeposit("ACC001", "2020-01-01", 5.0, 10000, "2025-12-31"));
    arr.add(ConditionalDeposit("ACC002", "2021-02-15", 4.5, 50000, "2025-12-31", "Until marriage"));
    std::cout << "Initial array:\n";
    arr.printAll(std::cout);

    arr.save(filename);
    std::cout << "Array saved to '" << filename << "'.\n";

    DepositArray loaded;
    loaded.load(filename);
    std::cout << "Loaded array from file:\n";
    loaded.printAll(std::cout);

    std::cout << "Removing first element...\n";
    loaded.remove(0);
    std::cout << "After removal:\n";
    loaded.printAll(std::cout);

    loaded.add(DemandDeposit("ACC003", "2024-03-10", 7.0, 150000, "2025-12-31"));
    std::cout << "Added new deposit, current array:\n";
    loaded.printAll(std::cout);
    loaded.save(filename);
    std::cout << "Updated array saved to file.\n";

    std::cin.ignore();
    std::cin.get();

    return 0;
}