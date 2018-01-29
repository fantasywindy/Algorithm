class Solution {
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        
        
        map<map<string, int>, int> ret = dfs(expression);
        
        map<string, int> table;
        for(int i = 0; i < evalvars.size(); ++i)
        {
            table[evalvars[i]] = evalints[i];
        }
        
        ret = convert(ret, table);
        
        vector<pair<string, int> > final;
        for(auto p : ret)
        {
            if(p.second == 0)
            {
                continue;
            }
            string str = "";
            for(auto item : p.first)
            {
                for(int i = 0; i < item.second; ++i)
                {
                    if(str == "")
                    {
                        str += item.first;
                    }
                    else
                    {
                        str += "*" + item.first;
                    }
                }
                
                
            }
            
            final.push_back({str, p.second});
        }
        
        sort(final.begin(), final.end(), [](const pair<string, int> & l, const pair<string, int> & r)
             {
                 return l.first.size() > r.first.size() || (l.first.size() == r.first.size() && l < r);
             });
        
        
        vector<string> temp;
        
        for(auto item : final)
        {
            string t = to_string(item.second);
            if(item.first != "")
            {
                t += "*" + item.first;
            }
            temp.push_back(t);
        }
        
        for(auto item : temp)
        {
            cout << item << endl;
        }
        
        return temp;
    }
    
    map<map<string, int>, int> convert(map<map<string, int>, int> in, map<string, int> table)
    {
        map<map<string, int>, int> ret;
        
        for(auto item : in)
        {
            map<string, int> newKey;
            int times = item.second;
            for(auto p : item.first)
            {
                if(isNum(p.first))
                {
                    times *= pow(stoi(p.first), p.second);
                    continue;
                }
                
                if(table.find(p.first) != table.end())
                {
                    times *= pow(table[p.first], p.second);
                }
                else
                {
                    newKey[p.first] = p.second;
                }
            }
            
            ret[newKey] += times;
        }
        
        return ret;
    }
    
    
    map<map<string, int>, int> dfs(string str)
    {
        if(str.find("(") == string::npos)
        {
            return parse(str);
        }
        
        
        vector<string> parts = splitIntoParts(str);
        for(auto & p : parts)
        {
            trimLeadingAndTailingZero(p);
        }
        
        return calc(parts);
    }
    
    map<map<string, int>, int> parse(string str)
    {
        trimLeadingAndTailingZero(str);
        if(str.find("*") == string::npos && str.find("+") == string::npos && str.find("-") == string::npos)
        {
            map<string, int> m;
            m[str] = 1;
            map<map<string, int>, int> ret;
            ret[m] = 1;
            return ret;
        }
        
        if(str.find("+") == string::npos && str.find("-") == string::npos && str.find("*") != string::npos)
        {
            stringstream ss(str);
            
            string temp;
            map<map<string, int>, int> ret;
            map<string, int> m;
            int times = 1;
            
            while(getline(ss, temp, '*'))
            {
                if(temp != "")
                {
                    trimLeadingAndTailingZero(temp);
                    
                    m[temp] += 1;
                }
            }
            
            ret[m] = 1;
            return ret;

        }
        
        vector<string> parts;
        
        int i = 0;
        
        while(i < str.size())
        {
            if(str[i] != ' ')
            {
                string temp;
                while(i < str.size() && (str[i] != '+' && str[i] != '-'))
                {
                    temp.push_back(str[i]);
                    ++i;
                }
                
                trimLeadingAndTailingZero(temp);
                parts.push_back(temp);
                
                if(i != str.size())
                {
                    parts.push_back(string(1, str[i]));
                    ++i;
                }
            }
            else{
                ++i;
            }
        }
        
        return calc(parts);
        
        
    }
    bool isNum(string str)
    {
        int cnt = count_if(str.begin(), str.end(), [](char c)
                           {
                               return c >= '0' && c <= '9';
                           });
        return cnt == str.size();
    }
    
    bool isOperator(string str)
    {
        return str == "*" || str == "+" || str == "-";
    }
    
    map<map<string, int>, int> calc(vector<string> & parts)
    {
        stack< map<map<string, int>, int> > operands;
        
        int i = 0;
        stack<string> operators;
        
        bool sign = true;
        
        while(i < parts.size())
        {
            if(isOperator(parts[i]))
            {
                if(parts[i] == "+")
                {
                    sign = true;
                    ++i;
                }
                else if(parts[i] == "-")
                {
                    sign = false;
                    ++i;
                }
                else
                {
                    operators.push("*");
                    ++i;
                }
            }
            else
            {
                if(operators.empty() == false && operators.top() == "*")
                {
                    auto prev = operands.top();
                    auto cur = dfs(parts[i]);
                    operands.pop();
                    operators.pop();
                    auto new_cur = multi(prev, cur);
                    operands.push(new_cur);
                    ++i;
                }
                else{
                    auto cur = dfs(parts[i]);
                    if(sign == false)
                    {
                        rev(cur);
                        sign = true;
                    }
                    operands.push(cur);
                    ++i;
                }
            }
        }
        
        while(operands.size() >= 2)
        {
            auto right = operands.top();
            operands.pop();
            auto left = operands.top();
            operands.pop();
            
            auto ret = add(left, right, true);
            operands.push(ret);
        }
        
        return operands.top();
    }
    
    void rev( map<map<string, int>, int> & left)
    {
        for(auto & p : left)
        {
            p.second *= -1;
        }
    }
    
    map<map<string, int>, int> add( map<map<string, int>, int> left,  map<map<string, int>, int> right, bool isAdd)
    {
        map<map<string, int>, int> ret;
        
        for(auto p1 : left)
        {
            ret[p1.first] += p1.second;
        }
        
        for(auto p2 : right)
        {
            if(isAdd == true)
            {
                ret[p2.first] += p2.second;
            }
            else
            {
                ret[p2.first] -= p2.second;
            }
        }
        
        return ret;
        
    }
    
    
    map<map<string, int>, int> multi(map<map<string, int>, int> left, map<map<string, int>, int> right)
    {
        map<map<string, int>, int> ret;
        for(auto p1 : left)
        {
            for(auto p2: right)
            {
                //
                map<string, int> new_key;
                for(auto key1 : p1.first)
                {
                    new_key[key1.first] += key1.second;
                }
                
                for(auto key2 : p2.first)
                {
                    new_key[key2.first] += key2.second;
                }
                
                ret[new_key] += p1.second * p2.second;
            }
        }
        
        return ret;
    }
    
    
    void trimLeadingAndTailingZero(string & s)
    {
        while(s.size() != 1 && s.front() == ' ')
        {
            s.erase(s.begin());
        }
        
        while(s.size() != 1 && s.back() == ' ')
        {
            s.pop_back();
        }
    }
    
    vector<string> splitIntoParts(string exp)
    {
        int i = 0;
        int n = exp.size();
        vector<string> ret;
        while(i < n)
        {
            if(exp[i] == '(')
            {
                int left = 1;
                ++i;
                string temp;
                while(i < n)
                {
                    if(exp[i] == '(')
                    {
                        temp.push_back(exp[i]);
                        ++left;
                        ++i;
                    }
                    else if(exp[i] == ')')
                    {
                        --left;
                        if(left == 0)
                        {
                            ++i;
                            break;
                        }
                        else
                        {
                            temp.push_back(exp[i]);
                            ++i;
                        }
                    }
                    else
                    {
                        temp.push_back(exp[i]);
                        ++i;
                    }
                }
                
                ret.push_back(temp);
            }
            else if(exp[i] == ' ')
            {
                ++i;
            }
            else
            {
                string temp;
                while(i < n && exp[i] != ' ')
                {
                    temp.push_back(exp[i]);
                    ++i;
                }
                
                ret.push_back(temp);
            }
        }
        
        return ret;
    }
};