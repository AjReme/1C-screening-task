completor = files('completor.cpp')
completor_lib = library(
  'completor',
  completor
)

main = files('main.cpp')
console_app = executable(
  'app',
  main,
  link_with: [ completor_lib ]
)

