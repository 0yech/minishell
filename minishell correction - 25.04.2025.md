# Broken stuff
- [x] export concat is broken
- [x] ctrl \ should send SIGQUIT to children (for example, launching `cat` without any argument and then pressing ctrl \ should send sigquit)
  same thing with ctrl c which should interrupt the child process, set the signal to SIGDFLT instead of SIGINT when entering forking)
- [x] cat | cat | ls is not only broken but doesn't execute ls before the cats (why does bash do that? what's different?)
  **pipelines aren't executed sequentially, they are launched all at once and the pipes are the ones determining when the commands get the input**
  For example in the case above, ls doesn't wait for input since it doesn't read it. Thus, ls should be executed before both the cats
- [x] exit builtin shouldn't accept alphabetic characters as an exit status (if there's one exit with exit status 2)
- [ ] prompt is kinda annoying, try to do something nice with readline
- [x] launching minishell without an env completely breaks the environment (env -i ./minishell)
- [x] `cat << END | << EOF cat` is sometimes broken, sometimes not (half the time a syntax is thrown, half the time the heredoc executes and cat doesn't)