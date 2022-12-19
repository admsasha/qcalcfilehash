Summary:	Hash calculator
Name:		qcalcfilehash
Version:	1.1.0
Release:	alt1
License:	GPLv3+
Group:		File tools
Url:		https://bitbucket.org/admsasha/qcalcfilehash
Source0:	%{name}-%{version}.tar

BuildRequires:	qt5-tools
BuildRequires:	pkgconfig(openssl)
BuildRequires:	pkgconfig(Qt5Core)
BuildRequires:	pkgconfig(Qt5Gui)
BuildRequires:	pkgconfig(Qt5Widgets)

%description
Hash calculator (SHA1, SHA-224, SHA-256, SHA-384, SHA-512, MD5, CRC32, CRC8
and also GOST R 34.11-94, GOST R 34-11-2012 (Streebog) 256 and 512 bit).

%prep
%setup -q

%build
%qmake_qt5
%make_build

%install
%makeinstall INSTALL_ROOT=%{buildroot}

%files
%doc README.md
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/%{name}/
%{_iconsdir}/hicolor/*/apps/%{name}.png

%changelog
* Mon Dec 19 2022 Alexander Danilov  <admsasha@altlinux.org> 1.1.0-alt1
- release 1.1.0
- added GOST algorithms

* Wed Dec 14 2022 Alexander Danilov  <admsasha@altlinux.org> 1.0.8-alt1
- release 1.0.8

* Wed Aug 12 2020 Alexander Danilov  <admsasha@altlinux.org> 1.0.7-alt1
- release 1.0.7

* Thu Aug 19 2019 Alexander Danilov  <admsasha@altlinux.org> 1.0.6-alt1
- release 1.0.6

* Fri Aug  2 2019 Alexander Danilov  <admsasha@altlinux.org> 1.0.5-alt1
- release 1.0.5
