project(
  '1C-screening-task',
  'cpp',
  default_options: [
    'warning_level=3',
    'buildtype=debugoptimized'
  ]
)

subdir('src')

if get_option('enable-tests')
  subdir('tests')
endif

doxygen = find_program(
  'doxygen',
  required: false
)
if doxygen.found()
  generate_docs = run_target(
    'generate-docs',
    command: [
      doxygen,
      'docs/doxycfg/doxyfile'
    ]
  )
else
  warning('Doxygen was\'nt found. "generate-docs" target won\'t be added.')
endif
