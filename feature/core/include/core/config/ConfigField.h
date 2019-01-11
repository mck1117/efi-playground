#pragma once

#include <sstream>
#include <list>

class PrefixStack
{
    std::list<std::string> m_stack;
    std::string m_prefix;

    void update()
    {
        std::stringstream str;

        for (auto i = m_stack.begin(); i != m_stack.end(); i++)
        {
            str << *i;
        }

        m_prefix = str.str();
    }

public:
    void push(const std::string& str)
    {
        m_stack.push_back(str);

        update();
    }

    void pop()
    {
        m_stack.pop_back();

        update();
    }

    std::string get() const
    {
        return m_prefix;
    }
};
class PrefixStacker
{
private:
    PrefixStack & m_stk;
public:
    PrefixStacker(PrefixStack& stk, const std::string& str)
        : m_stk(stk)
    {
        stk.push(str);
    }

    ~PrefixStacker()
    {
        m_stk.pop();
    }
};

template <int TMin, int TMax, int TPrecision>
struct FloatConfigField
{
    float Value;

    constexpr uintptr_t GetOffset(void* base)
    {
        return (uintptr_t)(&Value) - (uintptr_t)base;
    }

    void Print(std::stringstream& str, void* base, const char* name, PrefixStack& prefix, const char* units)
    {
        str << prefix.get() << name << " = scalar, F32, " << GetOffset(base) << ", \"" << units << "\", 0, 0, " << TMin << ", " << TMax << ", " << TPrecision << std::endl;
    }

    void Print(std::stringstream& str, void* base, PrefixStack& prefix, const char* name)
    {
        Print(str, base, name, prefix, "");
    }
};

struct pid_config
{
    FloatConfigField<-100, 100, 2> kP;
    FloatConfigField<-100, 100, 2> kI;
    FloatConfigField<-100, 100, 2> kD;

    void Print(std::stringstream& str, void* base, PrefixStack& prefix, const char* name)
    {
        PrefixStacker prefixer(prefix, name);

        kP.Print(str, base, prefix, "kp");
        kI.Print(str, base, prefix, "ki");
        kD.Print(str, base, prefix, "kd");
    }
};

struct test_config
{
    pid_config a;
    pid_config b;

    void Print(std::stringstream& str, void* base, PrefixStack& prefix, const char* name)
    {
        PrefixStacker prefixer(prefix, name);

        a.Print(str, base, prefix, "pid_a_");
        b.Print(str, base, prefix, "pid_b_");
    }
};

struct test_config_big
{
    test_config confa;
    test_config confb;

    void Print(std::stringstream& str, void* base, PrefixStack& prefix, const char* name)
    {
        PrefixStacker prefixer(prefix, name);

        confa.Print(str, base, prefix, "a_");
        confb.Print(str, base, prefix, "b_");
    }
};
