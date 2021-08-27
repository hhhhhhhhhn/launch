#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	extern char** environ;

	pid_t pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Failed to fork\n");
		exit(1);
	}

	if (pid > 0) {
		exit(0);
	}

	umask(0);

	if (setsid() < 0) {
		fprintf(stderr, "Failed to setsid\n");
		exit(1);
	}

	chdir("/");

	if (freopen("/dev/null", "r", stdin) == NULL) {
		fprintf(stderr, "Failed to redirect stderr\n");
		exit(1);
	}

	if (freopen("/dev/null", "r", stdout) == NULL) {
		fprintf(stderr, "Failed to redirect stdout\n");
		exit(1);
	}

	if (freopen("/dev/null", "r", stderr) == NULL) {
		fprintf(stderr, "Failed to redirect stderr\n");
		exit(1);
	}

	char** args = {NULL};

	execvp(argv[1], args);
}
