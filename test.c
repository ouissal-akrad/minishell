#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

 // char *plus = ft_strchr(tmp, '+');
                    // if(ft_strchr(tmp, '=') != NULL && plus != NULL && plus < ft_strchr(tmp, '='))
                    // {
                    //     puts("here");
                    //     prev = ft_substr(tmp, 0, plus - tmp);
                    //     rest = ft_strdup((plus + 1) + 1);
                    // }
                        // if(plus!= NULL)
                        // {
                        //     puts("here");
                        //     // Concatenate the new value with the old value of the variable
                        //     char *new_val = ft_strjoin(existing_var->val, rest);
                        //     if (new_val == NULL)
                        //     {
                        //         free(tmp);
                        //         return (env);
                        //     }
                        //     free(existing_var->val);
                        //     existing_var->val = new_val;
                        // }

                        void is_valid(char *str)
{
	int i = 1;
	while(str[i])
	{
        if(str[i] == '=')
            break;
		if((ft_isalpha(str[0]) || str[0] == '_') && ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else 
			return(0);
	}
	return(1);
}