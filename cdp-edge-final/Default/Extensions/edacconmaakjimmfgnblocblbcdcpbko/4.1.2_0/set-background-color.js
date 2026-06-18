// todo: figure out way to localize key between here and app
if (
  localStorage.getItem('nxs.theme') === 'dark' ||
  (localStorage.getItem('nxs.theme') !== 'light' &&
    window.matchMedia?.('(prefers-color-scheme: dark)').matches)
) {
  // todo: figure out way to localize color between here and app
  document.documentElement.style.backgroundColor = '#1e1e1e'
}
