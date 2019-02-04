# build-utils
Various tools to make building easier.

* Depend is a simple first-level bash version of dependencies extraction. It opens the source files and lists their includes. Works fine most of the times, but doesn't deal with includes with includes that are part of you project.

* Depynd is a more robust (but still flaky) Python version. It deals recursively with in-project dependencies, ignores system includes and absolute paths.

To use either, copy the script in the same directory as your `Makefile` and add it the rule:

```
depend:
	@./make-depend.py "$(INCLUDES)" "$(SOURCES)" > .depend>
```

and

```
-include .depend
```

somewhere in the Makefile. It will load the rules contained in <.depend> and make will do the rest.
