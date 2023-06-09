<div style="text-align:center">
    <h1 >
        MINISHELL
    </h1>
    <sub>SEASHELL</sub>
    <!-- <sub>by <a href="https://github.com/larskrabbe" target="_blank">&lt;larskrabbe&gt;</a> and <a href="https://github.com/JideOgunlana" target="_blank">&lt;jide_O&gt;</a></sub> -->
</div>
<header>
    <blockquote">
        <i><q>MINISHELL</q></i> is a project for the 42 school curriculum. It is a minified command line shell that can execute basic commands and handle redirections, pipes, environment variables, and built-in commands.
    </blockquote>
</header>
<nav>
    <h2>Table of Contents</h2>
    <ol>
        <li><a href=#overview>Project Overview</a></li>
        <li><a href="#features">Features</a></li>
        <li><a href="#built-in">Built-in-commands</a></li>
        <li><a href="#authors">Authors</a></li>
    </ol>
<nav>
<main>
    <section id="overview">
        <h2>Project Overview</h2>
        <p>
            The Minishell project is a complex and challenging project that requires the students to develop their problem-solving skills and to think critically about how to design and implement a shell program. It helps them develop their ability to read and understand documentation, implement complex data structures, and handle different types of inputs and outputs. Overall, the Minishell project is a great opportunity for students to put their programming skills into practice and develop a useful tool that can be used in their everyday life.
        </p>
    </section >
    <section id="features">
      <h2>Features</h2>
        <p>
            Our Minishell has the following features:
        </p>
        <ul>
            <li>
                Displays a prompt when waiting for a new command.
            </li>
            <li>
                Has a working history.
            </li>
            <li>
                Searches and launches the right executable (based on the PATH variable or using a relative or an absolute path).
            </li>
            <li>
                Does not use more than one global variable.
            </li>
            <li>
                Does not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
            </li>
            <li>
                Handles ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
            </li>
            <li>
                Handles " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
            </li>
            <li>
                Implements redirections: < should redirect input, > should redirect output, << should be given a delimiter, then read the input until a line containing the delimiter is seen, and >> should redirect output in append mode.
            </li>
            <li>
                Handles environment variables ($ followed by a sequence of characters) which should expand to their values.
            </li>
            <li>
                Handles $? which should expand to the exit status of the most recently executed foreground command.
            </li>
            <li>
                Handles ctrl-C, ctrl-D, and ctrl-\ which should behave like in bash.
            </li>
            <li>
                In interactive mode, ctrl-C displays a new prompt on a new line, ctrl-D exits the shell, and ctrl-\ does nothing.
            </li>
            <li>
                Implements built-in commands: echo with option -n, cd with only a relative or absolute path, pwd with no options, export with no options, unset with no options, env with no options or arguments, and exit with no options.
            </li>
        </ul>
    </section>
    <section id="built-in">
        <h2>Built-in Commands</h2>
        <p>
            Our Minishell implements the following built-in commands:
        </p>
        <ul>
            <li>
                echo with option -n
            </li>
            <li>
                cd with only a relative or absolute path
            </li>
            <li>
                pwd with no options
            </li>
            <li>
                export with no options
            </li>
            <li>
                unset with no options
            </li>
            <li>
                env with no options or arguments
            </li>
            <li>
                exit with no options
            </li>
        </ul>
    </section>
    <section id="authors">
        <h2>Authors</h2>
        <p>
            Minishell was created by <a href="https://github.com/larskrabbe" target="_blank">lkrabbe</a> and <a href="https://github.com/JideOgunlana" target="_blank">jide_O </a> as part of the 42 school curriculum.
        </p>
    </section>
</main>
