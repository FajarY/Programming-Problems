public class Solution {
    public bool IsValid(string s) {
        Stack<char> stack = new Stack<char>();
        for(int i = 0; i < s.Length; i++)
        {
            char current = s[i];
            if(current == '(' || current == '{' || current == '[')
            {
                stack.Push(current);
            }
            else if(current == ')')
            {
                if(stack.Count == 0)
                {
                    return false;
                }

                char check = stack.Peek();
                if(check != '(')
                {
                    return false;
                }
                else
                {
                    stack.Pop();
                }
            }
            else if(current == '}')
            {
                if(stack.Count == 0)
                {
                    return false;
                }

                char check = stack.Peek();

                if(check != '{')
                {
                    return false;
                }
                else
                {
                    stack.Pop();
                }
            }
            else if(current == ']')
            {
                if(stack.Count == 0)
                {
                    return false;
                }

                char check = stack.Peek();

                if(check != '[')
                {
                    return false;
                }
                else
                {
                    stack.Pop();
                }
            }
        }

        return stack.Count == 0;
    }
}