bash -c -o pipefail "./exit_with_error.sh" 2>&1 | tee "$GITHUB_WORKSPACE/TestOutput.log"
