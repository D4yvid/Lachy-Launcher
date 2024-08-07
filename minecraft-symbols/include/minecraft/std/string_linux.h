#pragma once

#include <cstring>
#include <string>

namespace mcpe
{

  struct string
  {
   private:
    void *ptr;

   public:
    static mcpe::string *empty;

    string();
    string(const char *str);
    string(const char *str, size_t len);
    string(const string &str);
    inline string(const std::string &str) : string(str.c_str(), str.length())
    {
    }
    string(string &&str);
    ~string();

    string &operator=(const string &str);

    void resize(std::size_t size);

    size_t length() const;
    const char *c_str() const;

    string operator+(const string &str);

    bool operator==(const string &s) const
    {
      if (s.ptr == ptr) return true;
      if (s.length() != length()) return false;
      return (memcmp(c_str(), s.c_str(), length()) == 0);
    }

    bool operator<(const string &s) const
    {
      int d = memcmp(c_str(), s.c_str(), std::min(length(), s.length()));
      if (d < 0) return true;
      if (d == 0) return length() < s.length();
      return false;
    }

    inline std::string std() const
    {
      return std::string(c_str(), length());
    }
  };

}  // namespace mcpe

std::ostream &operator<<(std::ostream &, const mcpe::string &);
