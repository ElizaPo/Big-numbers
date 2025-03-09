#include <iostream>
using namespace std;

const unsigned short max_string=256;
const char zero_char='0';
const char nine_char='9';
const char error_char='E';
const char minus_char='-';
const unsigned short error=255;
const size_t max_allow_length=9;

struct DivResult {
    string R;
    string Q;
};

unsigned short char_to_digit(char ch) {
    if (ch>=zero_char and ch<=nine_char) { return ch-zero_char; }
    return error;
}

char digit_to_char(unsigned short value) {
    if (value>=0 and value<=9) { return value+zero_char; }
    return error_char;
}

string get_zero() {
    return {zero_char}; }

bool is_positive(const string & sv) {
    return (sv.size()>0 and sv[0]!=minus_char); }

bool is_valid(const string & sv) {
    if (sv.size() > max_string) { return false; }
    size_t i=0;
    if (not is_positive(sv)) {
        ++i;
        if (sv.size()<2 or char_to_digit(sv[1])==0) {return false; }
    }

    while (i<sv.size()) {
        if(char_to_digit(sv[i])==error){ return false; }
        ++i;
    }
    return true;
}

bool is_zero(const string & sv) {
    if (sv.size()==0) {return false;}
    for (size_t i=0; i<sv.size(); ++i) {
        if (char_to_digit(sv[i])!=0 ) { return false; }
    }
    return true;
}

string reverse_sign(string s_value) {
    if (not is_positive(s_value))
    { s_value.erase(0,1); }
    else if (not is_zero(s_value))
    { s_value.insert(0, 1, minus_char); }
    return s_value;
}

bool left_smaller_than_right(const string & svl, const string & svr) {
    if (svr.size()>svl.size())
    { return true; }
    else if (svl.size()>svr.size())
    { return false; }
    else
    {
        size_t svl_i=0;
        size_t svr_i=0;

        while(svl_i<svl.size())
        {
            if (char_to_digit(svl[svl_i])<char_to_digit(svr[svr_i]))
            { return true; }
            else if(char_to_digit(svl[svl_i])>char_to_digit(svr[svr_i]))
            { return false; }
            ++svl_i;
            ++svr_i;
        }
    }
    return false;
}

string shift_left(string sv, size_t n) {
    for (size_t i=0;i<n;++i)
    { sv.push_back(digit_to_char(0)); }
    return sv;
}

string shift_right(string sv, size_t n) {
    if (n>=sv.size())
    { return get_zero(); }
    size_t new_length = sv.size()-n;
    sv.resize(new_length);
    return sv;
}

string trim_left(string sv, size_t n) {
    if (sv.size()>n)
    { sv.erase(0, sv.size()-n); }
    return sv;
}

string cut_left_zeros (string sv) {
    while (sv.size()>1 and char_to_digit(sv[0])==0)
    { sv.erase(0,1); }
    return sv;
}

unsigned long long abs_value_2(const string & sv) {
    if (sv.size()<=max_allow_length)
    { return stoull(sv); }
    return 0;
}

string add_abs(string svl, string svr) {
    unsigned short res(0);
    auto max_size = max(svl.size(), svr.size());

    string result(max_size+1, digit_to_char(0));

    auto svl_it=svl.size();
    auto svr_it=svr.size();
    auto res_it=result.size();
    while (res_it>0) {
        if (svl_it>0) {
            --svl_it;
            res+=char_to_digit(svl[svl_it]);
        }

        if (svr_it>0) {
            --svr_it;
            res+=char_to_digit(svr[svr_it]);
        }

        --res_it;
        result[res_it] = digit_to_char(res % 10);
        res=res/10;
    }

    if (char_to_digit(result[0])==0) {
        result.erase(0,1); }
    return result;
}

string sub_abs(string svl, const string & svr) {
    unsigned char additional = 0;

    auto svr_it=svr.size();
    auto svl_it=svl.size();
    while (svr_it>0) {
        --svr_it;
        --svl_it;
        if (char_to_digit(svl[svl_it])<additional+char_to_digit(svr[svr_it])) {
            svl[svl_it]=digit_to_char(char_to_digit(svl[svl_it])+10-additional-char_to_digit(svr[svr_it]));
            additional = 1;
        }
        else {
            svl[svl_it]=digit_to_char(char_to_digit(svl[svl_it])-additional-char_to_digit(svr[svr_it]));
            additional = 0;
        }
    }

    while (additional and svl_it>0) {
        --svl_it;
        if(char_to_digit(svl[svl_it])<additional) {
            svl[svl_it]=digit_to_char(char_to_digit(svl[svl_it])+10-additional);
            additional = 1;
        }
        else {
            svl[svl_it]=digit_to_char(char_to_digit(svl[svl_it])-additional);
            additional = 0;
        }
    }

    while (svl.size()>1 and char_to_digit(svl[0])==0) {
        svl.erase(0,1);
    }
    return svl;
}

string mul_abs(string svl, string svr) {
    size_t max_length = max(svl.size(), svr.size());
    if (max_length<=max_allow_length) {
        auto res = abs_value_2(svl)*abs_value_2(svr);
        return to_string(res);
    }
    else {
        size_t low_length = max_length/2;
        auto vll=trim_left(svl, low_length);
        auto vrl=trim_left(svr, low_length);
        auto vlh=shift_right(svl, low_length);
        auto vrh=shift_right(svr, low_length);

        auto mh1 = mul_abs(vlh, vrh);
        auto res = shift_left(mh1, 2*low_length);

        auto mh2 = mul_abs(vll, vrh);
        res = add_abs(res, shift_left(mh2, low_length));

        auto mh3 = mul_abs(vlh, vrl);
        res = add_abs(res, shift_left(mh3, low_length));

        auto mh4 = mul_abs(vll, vrl);
        res = add_abs(res, mh4);

        res = cut_left_zeros(res);
        return res;
    }
}

DivResult div_simple(string svn, const string & svd) {
    const string one_str = "1";
    DivResult res;

    if (is_zero(svd)) {
        res.Q="Error Division by Zero!!!";
        res.R=res.Q;
        return res;
    }

    res.R=svn;
    res.Q=get_zero();
    while (left_smaller_than_right(svd, res.R)) {
        res.R=sub_abs(res.R, svd);
        res.Q=add_abs(res.Q, one_str);
    }
    if (not left_smaller_than_right(res.R, svd)) {
        res.R=sub_abs(res.R, svd);
        res.Q=add_abs(res.Q, one_str);
    }
    res.R=cut_left_zeros(res.R);
    res.Q=cut_left_zeros(res.Q);
    return res;
}

DivResult div_abs(string svn, const string & svd) {
    DivResult res;

    if (is_zero(svd)) {
        res.Q="Error Division by Zero!!!";
        res.R=res.Q;
        return res;
    }

    if (left_smaller_than_right(svn, svd)) {
        res.Q=get_zero();
        res.R=svn;
        return res;
    }

    size_t svn_it = 0;
    string tmp_n = get_zero();

    while (svn_it<svn.size()) {
        if (left_smaller_than_right(tmp_n, svd)) {
            res.Q=cut_left_zeros(res.Q);
            if (not is_zero(res.Q)) {
                res.Q=shift_left(res.Q, 1);
            }
            tmp_n.push_back(svn[svn_it]);
            tmp_n=cut_left_zeros(tmp_n);
            ++svn_it;
        }
        else {
            auto simple_res = div_simple(tmp_n, svd);
            res.Q=add_abs(res.Q, simple_res.Q);
            tmp_n=simple_res.R;
            res.R=simple_res.R;
            tmp_n=cut_left_zeros(tmp_n);
        }
    }

    if (not left_smaller_than_right(tmp_n, svd)) {
        auto simple_res = div_simple(tmp_n, svd);
        res.Q=add_abs(res.Q, simple_res.Q);
        tmp_n=simple_res.R;
        res.R=simple_res.R;
    }

    return res;
}

string sum(string vl, string vr) {
    string result;
    auto vl_positive=is_positive(vl);
    auto vr_positive=is_positive(vr);

    if (vl_positive==vr_positive) {
        if (vl_positive) {
            result = add_abs(vl, vr);
        }
        else {
            result = reverse_sign(add_abs(reverse_sign(vl), reverse_sign(vr)));
        }
    }
    else {
        if (not vl_positive) {
            vl=reverse_sign(vl);
        }
        if (not vr_positive) {
            vr=reverse_sign(vr);
        }
        if (left_smaller_than_right(vl, vr)) {
            result=sub_abs(vr, vl);
            result=cut_left_zeros(result);
            if (not vr_positive) {
                result=reverse_sign(result);
            }
        }
        else {
            result=sub_abs(vl, vr);
            result=cut_left_zeros(result);
            if (not vl_positive) {
                result=reverse_sign(result);
            }
        }
    }
    return result;
}

string sub(string vl, string vr) {
    return (sum((vl), reverse_sign(vr)));
}

string mul(string vl, string vr) {
    auto vl_positive=is_positive(vl);
    auto vr_positive=is_positive(vr);
    if (not vl_positive) { vl = reverse_sign(vl); }
    if (not vr_positive) { vr = reverse_sign(vr); }

    auto result = mul_abs(vl, vr);
    if (vl_positive!=vr_positive) {
        result=reverse_sign(result); }
    return result;
}

DivResult full_div(string vl, string vr) {
    if (is_zero(vr)) {
        return {"Error Division by Zero!!!","Error Division by Zero!!!"}; }

    auto vl_positive=is_positive(vl);
    auto vr_positive=is_positive(vr);
    if (not vl_positive) {
        vl = reverse_sign(vl); }
    if (not vr_positive) {
        vr = reverse_sign(vr); }
    auto res = div_abs(vl, vr);
    if (vl_positive != vr_positive) {
        res.Q = reverse_sign(res.Q);
        res.R = reverse_sign(res.R);
    }
    return res;
}

string div(string vl, string vr) {
    return full_div(vl, vr).Q; }

string mod(string vl, string vr) {
    return full_div(vl, vr).R; }

int main() {
    int numTests;
    cin >> numTests;
    cin.ignore();

    for (int i = 0; i < numTests; ++i) {
        string num1, num2, result, input;
        char operation;
        getline(cin, input);

        if (input.length() > max_string) {
            cout << "Error" << endl;
            continue;
        }

        size_t pos = input.find_first_of("+-*/");
        if (pos > 0 and pos < input.length() - 1) {
            string num1 = input.substr(0, pos);
            char operation = input[pos];
            string num2 = input.substr(pos + 1);
            if (not is_valid(num1)){
                cout << "Error" << endl;
                continue;
            }
            if (not is_valid(num2)){
                cout << "Error" << endl;
                continue;
            }

            if (operation == '+') { result = sum(num1, num2); }
            else if (operation == '-') { result = sub(num1, num2); }
            else if (operation == '*') { result = mul(num1, num2); }
            else if (operation == '/') { result = div(num1, num2); }
            else { result = "Error"; }
            cout << result << endl;
        }
    }

    return 0;
}