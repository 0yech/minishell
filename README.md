![image](https://github.com/user-attachments/assets/94e4623d-3937-405a-a29d-4ba0c27c78d6)

# Minishell

A Unix shell made at 42 School.

By [0yech](https://github.com/0yech) and [Aisling Fontaine](https://github.com/FireInsidE-fie)

---

## Description

Minishell consists of recreating a minimalist unix shell with very few external tools and libraries. The project is heavily focused on parsing and handling the prompts properly. It is well known for being one of 42's hardest common core projects. It's also its first group project, which definitely adds some complexity to it for anyone unfamiliar with git or versioning concepts.

Some core features to implement would include `parsing`, `pipes`, `redirections`, `signal handling`, `built-ins` and `environment management`.

To see all the requirements, check [en.subject.pdf](https://github.com/0yech/minishell/blob/main/en.subject.pdf)

This version does not include all bonuses, as we focused on its reliability.

If you're getting into Minishell, sit down with your teammate and do a week or two of research before coding anything. Also, close your file descriptors and don't leak memory.

---

## Features

- Command execution with absolute or relative paths  
- Quote handling (`'` and `"`)  
- Environment variable expansion (`$VAR`)  
- Pipes, redirections and heredocs (`|`, `>`, `>>`, `<`, `<<`)  
- Signal handling (`ctrl-C`, `ctrl-D`, `ctrl-\`)  
- Proper exit and return values  
- Git branch display in the prompt
- Help menu (`./minishell -h`)
- Things shells do

---

## Builtins

| Command | Description |
|----------|-------------|
| echo | Display a line of text |
| cd | Change the current directory |
| pwd | Print the current working directory |
| export | Set environment variables |
| unset | Remove environment variables |
| env | Display the environment |
| exit | Exit the shell |

---

## Return status examples

| Code | Status |
|------|----------|
| 127 | Command not found |
| 126 | Is a directory |
| 126 | Permission denied |
| 2 | Syntax error |

---

## Demo

<p align="center">
  <img src="https://github.com/user-attachments/assets/b0ad81ac-0749-415f-a0f0-08ae0504fce5" alt="minishell demo" width="800">
</p>
