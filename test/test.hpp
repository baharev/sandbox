#ifndef TEST_HPP_
#define TEST_HPP_
#include <memory>

class test {

public:

    template <class T>
    test(T x) : self(new model<T>(std::move(x))) { }

    test(test&&) noexcept = default;

    test& operator=(test&&) noexcept = default;

    void execute(const std::vector<std::string>& args) const {

        self->init(args);

        self->run();
    }

private:

    struct test_concept {

        virtual void init(const std::vector<std::string>& args) = 0;

        virtual void run() = 0;

        virtual ~test_concept() = default;
    };

    template <typename T>
    struct model : test_concept {

        model(T x) : test_(std::move(x)) { }

        void init(const std::vector<std::string>& args) final override { test_.init(args); }

        void run() final override { test_.run(); }

        T test_;
    };

    std::unique_ptr<test_concept> self;
};

#endif
