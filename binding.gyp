
{
  'targets': [
    {
      'target_name': 'napi_edge_nativeclr',
      'win_delay_load_hook': 'false',
      'include_dirs': [
      ],
      'cflags+': [
        '-DHAVE_NATIVECLR -std=c++11'
      ],
      'xcode_settings': {
        'OTHER_CFLAGS': [
          '-DHAVE_NATIVECLR'
        ]
      },
      'conditions': [
        [
          'OS=="win"',
          {
            'sources+': [
              'src_napi/native/clr-func.cpp',
              # 'src_napi/native/utils.cpp',
              # 'src_napi/native/clrfunc.cpp',
              # 'src_napi/native/clrfuncinvokecontext.cpp',
              # 'src_napi/native/nodejsfunc.cpp',
              # 'src_napi/native/nodejsfuncinvokecontext.cpp',
              # 'src_napi/native/persistentdisposecontext.cpp',
              # 'src_napi/native/clrfuncreflectionwrap.cpp',
              # 'src_napi/native/clractioncontext.cpp',
              # 'src_napi/common/v8synchronizationcontext.cpp',
              # 'src_napi/common/callbackhelper.cpp',
              'src_napi/common/bindings.cpp'
            ]
          }
        ]
      ],
      'configurations': {
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              # this is out of range and will generate a warning and skip adding RuntimeLibrary property:
              'RuntimeLibrary': -1,
              # this is out of range and will generate a warning and skip adding RuntimeTypeInfo property:
              'RuntimeTypeInfo': -1,
              'BasicRuntimeChecks': -1,
              'ExceptionHandling': '0',
              'AdditionalOptions': [
                '/clr',
                '/wd4506',
                '/DHAVE_NATIVECLR'
              ]
            },
            'VCLinkerTool': {
              'AdditionalOptions': [
                '/ignore:4248'
              ]
            }
          }
        },
        'Debug': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              # this is out of range and will generate a warning and skip adding RuntimeLibrary property:
              'RuntimeLibrary': 3,
              # this is out of range and will generate a warning and skip adding RuntimeTypeInfo property:
              'RuntimeTypeInfo': -1,
              'BasicRuntimeChecks': -1,
              'ExceptionHandling': '0',
              'AdditionalOptions': [
                '/clr',
                '/wd4506',
                '/DHAVE_NATIVECLR'
              ]
            },
            'VCLinkerTool': {
              'AdditionalOptions': [
                '/ignore:4248'
              ]
            }
          }
        }
      }
    }
  ]
}
